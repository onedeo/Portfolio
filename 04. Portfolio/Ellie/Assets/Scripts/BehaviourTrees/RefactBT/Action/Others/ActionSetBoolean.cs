namespace Scripts.BehaviourTrees.Monster
{
    public class ActionSetBoolean : MonsterNode
    {
        private BTData data;
        private bool boolean;

        public ActionSetBoolean(BTData data, bool boolean)
        {
            this.data = data;
            this.boolean = boolean;
        }
        public override NodeState Evaluate()
        {
            tree.SetBTData<bool>(data, boolean);
            return NodeState.SUCCESS;
        }
    }
}