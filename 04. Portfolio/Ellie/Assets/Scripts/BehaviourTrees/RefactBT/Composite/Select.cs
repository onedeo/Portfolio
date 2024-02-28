using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class Select : Node
    {
        private int current;
        public Select() : base() { }
        public Select(List<Node> childrens) : base(childrens) { }

        protected override void OnStart()
        {
            current = 0;
            isStarted = true;
        }
        public override NodeState Evaluate()
        {
            if (!isStarted)
                OnStart();
            for(int i=current;i<children.Count;i++)
            {
                current = i;
                var child = children[current];

                switch (child.Evaluate())
                {
                    case NodeState.FAILURE:
                        continue;
                    case NodeState.SUCCESS:
                        return NodeState.SUCCESS;
                    case NodeState.RUNNING:
                        return NodeState.RUNNING;
                    default:
                        continue;
                }
            }

            return NodeState.FAILURE;
        }
    }
}