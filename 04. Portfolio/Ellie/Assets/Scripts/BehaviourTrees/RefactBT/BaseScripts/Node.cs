using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
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
        protected Transform transform;
        public Node parent;
        protected List<Node> children;
        protected Tree baseTree;
        protected bool isStarted;
        protected bool isExited;

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
    }
}