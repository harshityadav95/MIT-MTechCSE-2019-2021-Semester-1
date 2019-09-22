int InsertionSort(int [],int,int);
int Quick(int [],int,int);
void Partition(int [],int,int,int);

int InsertionSort(int arr[],int low,int high)
{
    int x,y,temp;
    for(x=2;x<=high;x++)
    {
            y = x-1;
            temp=arr[x];
            while(y>0 && arr[y]>arr[y+1])
            {
                arr[y+1]=arr[y];
                y=y-1;
            }
            arr[y+1]=temp;
    }
    return 0;
}


int Quick(int arr[],int low,int high)
{
    int x,y,pivot,temp;
    pivot=arr[high];
    for(x=low,y=low-1;x<high;x++)
    {
        if(arr[x]<pivot)
        {
            y=y+1;
            arr[y]=arr[x];
        }
    }
    arr[high]=arr[y+1];
    arr[++y]=pivot;
    Partition(arr,low,y,high);
    return 0;
}


void Partition(int arr[],int low,int mid,int high)
{
    if(low<high)
    {
        Quick(arr,low,mid);
        Quick(arr,mid+1,high);
    }
    return;
}
