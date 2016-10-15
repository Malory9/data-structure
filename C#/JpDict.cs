using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CST
{
    public static class Pair
    {
        public static Pair<T, TU> CreatePair<T, TU>(T first, TU second)
        {
            return new Pair<T, TU>(first, second);
        }
    }

    public class Pair<TF, TS> : IEquatable<Pair<TF, TS>>
    {
        private readonly EqualityComparer<TF> _fComparer = EqualityComparer<TF>.Default;
        private readonly EqualityComparer<TS> _sComparer = EqualityComparer<TS>.Default;


        public Pair(TF first, TS second)
        {
            First = first;
            Second = second;
        }

        public Pair()
        {
            First = default(TF);
            Second = default(TS);
        }


        public TF First { set; get; }
        public TS Second { set; get; }


        public bool Equals(Pair<TF, TS> other)
        {
            if (other == null) return false;
            if (ReferenceEquals(this, other)) return true;
            return _sComparer.Equals(Second, other.Second) && _fComparer.Equals(First, other.First);
        }


        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            return obj.GetType() == GetType() && Equals((Pair<TF, TS>)obj);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                var hashCode = _fComparer?.GetHashCode() ?? 0;
                hashCode = (hashCode * 397) ^ (_sComparer?.GetHashCode() ?? 0);
                hashCode = (hashCode * 397) ^ EqualityComparer<TF>.Default.GetHashCode(First);
                hashCode = (hashCode * 397) ^ EqualityComparer<TS>.Default.GetHashCode(Second);
                return hashCode;
            }
        }
    }

    public class JpDict<TF, TS> : IEnumerable<Pair<TF, TS>> where TF : IComparable<TF>
    {
        private readonly Comparer<TF> _tComparer = Comparer<TF>.Default;

        private Node _root;

        public Pair<TF, TS> FindMin()
        {
            if (_root == null)
                throw new ArgumentNullException($"FindMin", "no reference on root");
            return FindMin(_root);
        }

        private static Pair<TF, TS> FindMin(Node node)
        {
            while (true)
            {
                if (node.Left == null) return node.Pair;
                node = node.Left;
            }
        }


        public Pair<TF, TS> FindMax()
        {
            if (_root == null)
                throw new ArgumentNullException($"FindMax", "no reference on root");
            return FindMax(_root);
        }

        private static Pair<TF, TS> FindMax(Node node)
        {
            return node.Right == null ? node.Pair : FindMax(node.Right);
        }


        public void Add(Pair<TF, TS> pair)
        {
            Add(pair, ref _root);
        }

        private void Add(Pair<TF, TS> pair, ref Node node)
        {
            if (node == null)
                node = new Node(pair);
            else if (_tComparer.Compare(pair.First, node.Pair.First) > 0)
                Add(pair, ref node.Right);
            else Add(pair, ref node.Left);
        }

        public void Erase(TF priKey)
        {
            Erase(ref _root, priKey);
        }

        private void Erase(ref Node node, TF priKey)
        {
            if (node == null)
                return;
            if (priKey.CompareTo(node.Pair.First) > 0)
                Erase(ref node.Right, priKey);
            else if (priKey.CompareTo(node.Pair.First) < 0)
                Erase(ref node.Left, priKey);
            else
            {
                if (node.Left != null && node.Right != null)
                {
                    node.Pair = FindMax(node.Right);
                    Erase(ref node.Right, node.Pair.First);
                }
                else if (node.Left == null && node.Right == null)
                {
                    node = null;
                }
                else
                {
                    var selectedLis = node.Left ?? node.Right;
                    node = selectedLis;
                }
            }
        }

        public bool ContainsKey(TF key)
        {
            return this.Any((pair => pair.First.Equals(key)));

        }

        public TS this[TF key]
        {
            get
            {
                var pair = this.Find(_root, key);
                if (pair != null)
                    return pair.Second;
                else
                {
                    throw new ArgumentNullException($"this[]", "not exists");
                }

            }
            set { this.Find(_root, key).Second = value; }
        }

        public Pair<TF, TS> Find(Node node,TF key)
        {
            if (node == null)
                return null;
            if (_tComparer.Compare(node.Pair.First, key) < 0)
            {
              return  Find(node.Right, key);
            }
            if(_tComparer.Compare(node.Pair.First,key)>0)
                return Find(node.Left,key);
            {
                return node.Pair;
            }
        }

        public void Print()
        {
            Print(_root);
        }

        private static void Print(Node node)
        {
            while (true)
            {
                if (node == null) return;
                Print(node.Left);
                Console.Write($"{node.Pair.Second} ");
                node = node.Right;
            }
        }

        public class Node
        {
            public Node Left;
            public Node Right;

            public Node(Pair<TF, TS> val, Node left = null, Node right = null)
            {
                Pair = val;
                Left = left;
                Right = right;
            }

            public Pair<TF, TS> Pair { get; set; }
        }


        public IEnumerator<Pair<TF, TS>> GetEnumerator()
        {
            var lis = new List<Pair<TF, TS>>();

            GetEnumeratorHelper(_root, lis);

            return lis.GetEnumerator();
        }
        private void GetEnumeratorHelper(Node node, ICollection<Pair<TF, TS>> collection)
        {
            while (true)
            {
                if (node == null) break;
                GetEnumeratorHelper(node.Left, collection);
                collection.Add(node.Pair);
                node = node.Right;
            }
        }



        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
