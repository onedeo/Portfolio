namespace Scripts.BehaviourTrees.Monster
{
    public class ActionAssertBoolean : MonsterNode
    {
        private bool boolean;
        public ActionAssertBoolean(bool boolean)
        {
            this.boolean = boolean;
        }
        public override NodeState Evaluate()
        {
            if (boolean) return NodeState.SUCCESS;
            else return NodeState.FAILURE;
        }
    }
}
