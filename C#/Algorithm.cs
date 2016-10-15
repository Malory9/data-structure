using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CST
{
  public static class Algorithm
    {
        public static List<int> CountSort(IList<int> collection)
        {
            var valueCount = new JpDict<int, int>(); //自己写的Dictionary，FCL的添加后主键并不是有序的
            foreach (var i in collection)
                if (valueCount.ContainsKey(i))
                    valueCount[i]++;
                else
                    valueCount.Add(Pair.CreatePair(i, 1));

            var valueOrder = valueCount.Select(pair => new CountStruct(pair.First, pair.Second)).ToList();
            for (var i = 0; i < valueOrder.Count - 1; ++i) //设置Order为小于等于Value的数量
                valueOrder[i + 1] = new CountStruct(valueOrder[i + 1].Value, valueOrder[i + 1].Order + valueOrder[i].Order);

            var returnList = new List<int>(collection.Count);
            for (var i = 0; i < collection.Count; ++i)//填充为0
                returnList.Add(0);

            foreach (var countStruct in valueOrder)
            {
                var count = valueCount[countStruct.Value]; //解决相同数据的情况

                for (var i = 0; i < count; ++i)                                     //根据计数插入
                    returnList[countStruct.Order - i - 1] = countStruct.Value;
            }
            return returnList;
        }

        private struct CountStruct
        {
            public int Value { get; }
            public int Order { get; }

            public CountStruct(int value, int order)
            {
                Value = value;
                Order = order;
            }
        }

        private static void Swap<T>(IList<T> list, int left, int right)
        {
            T temp = list[left];
            list[left] = list[right];
            list[right] = temp;
        }
        public static void QSort<T>(IList<T> list)
        {
            QSort(list,Comparer<T>.Default);
        }

        public static void QSort<T> (IList<T> list, IComparer<T> comparer)
        {
            QSortImple(list,comparer,0,list.Count-1);
        }

        private static void QSortImple<T>(IList<T> list, IComparer<T> comparer,int beg,int end)
        {
            if (beg >= end)
                return;
            Random random = new Random();
            var randIndex = random.Next(list.Count - 1);
            Swap(list, 0, randIndex);
            int low = beg;
            int high = end;
            T key = list[low];

       
            while (low < high)
            {
                while (low<high&&comparer.Compare(list[high],key) >= 0)
                {
                    --high;
                }
                list[low] = list[high];

                while (low < high && comparer.Compare(list[low], key) <= 0)
                {
                    ++low;
                }
                list[high] = list[low];
            }
            list[low] = key;
            QSortImple(list,comparer,beg,low-1);
            QSortImple(list,comparer,low+1,end);
        }
    }
}
