from __future__ import division, print_function

import argparse
from mpi4py import MPI
import torch
import torch.nn.functional as F
from pynum import pynums
from torch import distributed, nn
from torch.utils import data
from torchvision import datasets, transforms


def distributed_is_initialized():
    if distributed.is_available():
        if distributed.is_initialized():
            return True
    return False


class Average(object):

    def __init__(self):
        self.sum = 0
        self.count = 0

    def __str__(self):
        return '{:.6f}'.format(self.average)

    @property
    def average(self):
        return self.sum / self.count

    def update(self, value, number):
        self.sum += value * number
        self.count += number


class Accuracy(object):

    def __init__(self):
        self.correct = 0
        self.count = 0

    def __str__(self):
        return '{:.2f}%'.format(self.accuracy * 100)

    @property
    def accuracy(self):
        return self.correct / self.count

    def update(self, output, target):
        with torch.no_grad():
            pred = output.argmax(dim=1)
            correct = pred.eq(target).sum().item()

        self.correct += correct
        self.count += output.size(0)


class Trainer(object):

    def __init__(self, model, optimizer, train_loader, test_loader, device):
        self.model = model
        self.optimizer = optimizer
        self.train_loader = train_loader
        self.test_loader = test_loader
        self.device = device

    def fit(self, epochs):
        pynums(epochs)
        for epoch in range(1, epochs + 1):
            train_loss, train_acc = self.train()
            test_loss, test_acc = self.evaluate()

            print(
                'Rank: {}/{},'.format(epoch, epochs),
                'train loss: {}, train acc: {},'.format(train_loss, train_acc),
                'test loss: {}, test acc: {}.'.format(test_loss, test_acc),
            )

    def train(self):
        self.model.train()

        train_loss = Average()
        train_acc = Accuracy()

        for data, target in self.train_loader:
            data = data.to(self.device)
            target = target.to(self.device)

            output = self.model(data)
            loss = F.cross_entropy(output, target)

            self.optimizer.zero_grad()
            loss.backward()
            self.optimizer.step()

            train_loss.update(loss.item(), data.size(0))
            train_acc.update(output, target)

        return train_loss, train_acc

    def evaluate(self):
        self.model.eval()

        test_loss = Average()
        test_acc = Accuracy()

        with torch.no_grad():
            for data, target in self.test_loader:
                data = data.to(self.device)
                target = target.to(self.device)

                output = self.model(data)
                loss = F.cross_entropy(output, target)

                test_loss.update(loss.item(), data.size(0))
                test_acc.update(output, target)

        return test_loss, test_acc


class Net(nn.Module):

    def __init__(self):
        super(Net, self).__init__()
        self.fc = nn.Linear(784, 10)

    def forward(self, x):
        return self.fc(x.view(x.size(0), -1))


class MNISTDataLoader(data.DataLoader):

    def __init__(self, root, batch_size, train=True):
        transform = transforms.Compose([
            transforms.ToTensor(),
            transforms.Normalize((0.1307,), (0.3081,)),
        ])

        dataset = datasets.MNIST(root, train=train, transform=transform, download=True)
        sampler = None
        if train and distributed_is_initialized():
            sampler = data.DistributedSampler(dataset)

        super(MNISTDataLoader, self).__init__(
            dataset,
            batch_size=batch_size,
            shuffle=(sampler is None),
            sampler=sampler,
        )

class Partition(object):

    def __init__(self, data, index):
        self.data = data
        self.index = index

    def __len__(self):
        return len(self.index)

    def __getitem__(self, index):
        data_idx = self.index[index]
        return self.data[data_idx]
def run(args):
    device = torch.device('cuda' if torch.cuda.is_available() and not args.no_cuda else 'cpu')

    model = Net()
    if distributed_is_initialized():
        model.to(device)
        model = nn.parallel.DistributedDataParallel(model)
    else:
        model = nn.DataParallel(model)
        model.to(device)

    optimizer = torch.optim.Adam(model.parameters(), lr=args.learning_rate)

    train_loader = MNISTDataLoader(args.root, args.batch_size, train=True)
    test_loader = MNISTDataLoader(args.root, args.batch_size, train=False)

    trainer = Trainer(model, optimizer, train_loader, test_loader, device)
    trainer.fit(args.world_size)

class DataPartitioner(object):

    def __init__(self, data, sizes=[0.7, 0.2, 0.1], seed=1234):
        self.data = data
        self.partitions = []
        rng = Random()
        rng.seed(seed)
        data_len = len(data)
        indexes = [x for x in range(0, data_len)]
        rng.shuffle(indexes)

        for frac in sizes:
            part_len = int(frac * data_len)
            self.partitions.append(indexes[0:part_len])
            indexes = indexes[part_len:]

    def use(self, partition):
        return Partition(self.data, self.partitions[partition])

def partition_dataset():
    dataset = datasets.MNIST('./data', train=True, download=True,
                             transform=transforms.Compose([
                                 transforms.ToTensor(),
                                 transforms.Normalize((0.1307,), (0.3081,))
                             ]))
    size = dist.get_world_size()
    bsz = 128 / float(size)
    partition_sizes = [1.0 / size for _ in range(size)]
    partition = DataPartitioner(dataset, partition_sizes)
    partition = partition.use(dist.get_rank())
    train_set = torch.utils.data.DataLoader(partition,
                                         batch_size=bsz,
                                         shuffle=True)
    return train_set, bsz
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--backend', type=str, default='gloo', help='Name of the backend to use.')
    parser.add_argument(
        '-i',
        '--init-method',
        type=str,
        default='tcp://127.0.0.1:23456',
        help='URL specifying how to initialize the package.')
    parser.add_argument('-s', '--epochs', type=int, default=1, help='Number of processes participating in the job.')
    parser.add_argument('-r', '--rank', type=int, default=0, help='Rank of the current process.')
    parser.add_argument('--world-size', type=int, default=5)
    parser.add_argument('--no-cuda', action='store_true')
    parser.add_argument('-lr', '--learning-rate', type=float, default=1e-3)
    parser.add_argument('--root', type=str, default='data')
    parser.add_argument('--batch-size', type=int, default=128)
    args = parser.parse_args()
    print(args)

    if args.world_size > 1:
        distributed.init_process_group(
            backend=args.backend,
            init_method=args.init_method,
            world_size=world_size,
            rank=args.rank,
        )

    run(args)
def average_gradients(model):
    size = float(dist.get_world_size())
    for param in model.parameters():
        dist.all_reduce(param.grad.data, op=dist.reduce_op.SUM)
        param.grad.data /= size

if __name__ == '__main__':
    main()
