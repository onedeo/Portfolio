using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public abstract class Tree : MonoBehaviour
    {
        protected Node root = null;

        private void Update()
        {
            if (root != null) root.Evaluate();
        }
        protected abstract void SetupTree(Node root);
    }
}