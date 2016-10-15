using System.Collections.Generic;

namespace CST
{
    internal sealed class Node
    {
        public int Count; //含有该节点字符前缀的字符串数目
        public Dictionary<char, Node> NextNodes { get; } //牺牲一定的时间，代表指向下一节点的分支
        public char? Val { get; set; } 
        public bool HasElement { set; get; } //该节点含有相应的字符串
        //由于C#在安全代码下无指针，现想到将val取char？模拟含空的情况
        public Node(char? val)
        {
            Count = 0;
            HasElement = false;
            Val = val;

            NextNodes = new Dictionary<char, Node>();
        }

    }

    public sealed class JpTrieTree
    {
        private Node _treeNode;


        public JpTrieTree()
        {
            _treeNode = new Node('\t'); //初始根节点设置为一个非正常字符串的值，仅仅用来占位而已
        }

        private void AddImple(string chars, int curIndex, int lastIndex, ref Node node)
        {
            while (true)
            {
                if (curIndex == lastIndex) //已到需添加字符串的结尾
                {
                    node.HasElement = true;
                    ++node.Count;
                    return;
                }
                if (node.Val == null) //分支的下一节点是存在的，但其值为空，模拟的是未存在该字符的情况
                {
                    node.Val = chars[curIndex];
                    ++curIndex;
                    continue;
                }


                if (!node.NextNodes.ContainsKey(chars[curIndex]))
                {
                    node.NextNodes.Add(chars[curIndex], new Node(null));
                    var toAdd = node.NextNodes[chars[curIndex]];
                    AddImple(chars, curIndex, lastIndex, ref toAdd);
                    node.Count++;
                }
                else
                {
                    var toAdd = node.NextNodes[chars[curIndex]];

                    AddImple(chars, curIndex + 1, lastIndex, ref toAdd);
                    ++node.Count;
                }


                break;
            }
        }

        public void Add(string str)
        {
            AddImple(str, 0, str.Length, ref _treeNode);
        }

        private bool ContainsImple(string chars, int curIndex, int lastIndex, Node node)
        {
            while (true)
            {
                if (curIndex + 1 == lastIndex)
                {
                    var nextNode = node.NextNodes[chars[curIndex]];
                    return (nextNode.Val == chars[curIndex]) && nextNode.HasElement;
                }


                if (!node.NextNodes.ContainsKey(chars[curIndex]))
                    return false;
                var chars1 = chars;
                var curIndex1 = curIndex;
                curIndex = curIndex + 1;
                node = node.NextNodes[chars1[curIndex1]];
            }
        }

        public bool Contains(string str)
        {
            if (str.Length == 1)
                return str[0] == _treeNode.Val;
            return ContainsImple(str, 0, str.Length, _treeNode);
        }
    }
}