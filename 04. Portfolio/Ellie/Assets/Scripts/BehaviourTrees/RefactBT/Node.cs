using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public enum NodeState
    {
        RUNNING,
        SUCCESS,
        FAILURE,
    }

    public class Node
    {
        protected NodeState state;
        //몬스터 노드가 노드를 상속받아서 몬스터 전용 노드를 만들면 더 좋을듯
        protected Monster monster;
        public Node parent;
        protected List<Node> children;

        private Dictionary<string, object> dataContext = new Dictionary<string, object>();

        public Node()
        {
            parent = null;
        }
        public Node(List<Node> children)
        {
            foreach (Node child in children)
                Attach(child);
        }
        public Node(Node child)
        {
            Attach(child);
        }
        protected virtual void OnStart() { }
        protected virtual void OnExit() { }
        public virtual NodeState Evaluate() => NodeState.FAILURE;

        protected void SetChildren(List<Node> children)
        {
            foreach (Node child in children)
                Attach(child);
        }
        
        private void Attach(Node node)
        {
            node.parent = this;
            children.Add(node);
        }
        public void SetData(string key, object value)
        {
            dataContext[key] = value;
        }
        public object GetData(string key)
        {
            object value = null;
            if (dataContext.TryGetValue(key, out value))
                return value;

            Node node = parent;
            while(node!=null)
            {
                value = node.GetData(key);
                if (value != null) return value;
                node = node.parent;
            }

            return null;
        }
        public bool ClearData(string key)
        {
            object value = null;
            if (dataContext.ContainsKey(key))
            {
                dataContext.Remove(key);
                return true;
            }
            Node node = parent;
            while (parent != null)
            {
                bool cleared = node.ClearData(key);
                if (cleared) return true;
                node = node.parent;
            }
            return false;
        }

    }
}