namespace Scripts.BehaviourTrees.Monster
{
    public class ActionPlayParticle : MonsterNode
    {
        private MonsterParticleController particleController;
        private MonsterParticleType particleType;

        public ActionPlayParticle(MonsterParticleType particleType)
        {
            particleController = tree.GetComponentData<MonsterParticleController>(MonsterComponentData.PARTICLE);
            this.particleType = particleType;
        }
        public override NodeState Evaluate()
        {
            particleController.PlayParticle(particleType);

            return NodeState.SUCCESS;
        }
    }
}
