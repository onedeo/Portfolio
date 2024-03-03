using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterAttackBase : MonoBehaviour
    {
        private MonsterBase monster;
        protected MonsterAudioController audioController;
        protected MonsterParticleController particleController;

        protected virtual void Awake()
        {
            if (audioController == null)
                audioController = GetComponent<MonsterAudioController>();
            if (particleController == null)
                particleController = GetComponent<MonsterParticleController>();
        }

        public virtual void ExecuteAttack() {}

        public void Attack(IBaseEventPayload payload)
        {
            monster.Attack(payload);
        }
    }
}
