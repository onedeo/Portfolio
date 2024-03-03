using System.Collections;
using Assets.Scripts.Combat;
using Assets.Scripts.StatusEffects;
using Channels.Combat;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterMeleeAttack : MonsterAttackBase
    {
        private MeleeAttackData data;
        private BoxCollider collider;
        private ParticleSystem particle;

        protected override void Awake()
        {
            base.Awake();

            // Collider Setting
            if (collider == null)
                collider = gameObject.AddComponent<BoxCollider>();
            collider.isTrigger = true;
            collider.size = data.colliderSize;
            gameObject.transform.localPosition = data.colliderOffset;
            collider.enabled = false;
        }
        public void SetInitialData(MeleeAttackData meleeData)
        {
            data = meleeData;
        }
        public override void ExecuteAttack()
        {
            if(data==null)
                Debug.LogFormat("{0} Has Not Initialized MeleeAttack : {0}, MeleeAttack" + transform.name);
            collider.enabled = true;
            StartCoroutine(DisableCollider());
        }
        private IEnumerator DisableCollider()
        {
            yield return new WaitForSeconds(data.colliderDuration);
            collider.enabled = false;
        }
        private void OnTriggerEnter(Collider other)
        {
            if(other.CompareTag("Player"))
            {
                if(other.gameObject.GetComponent<ICombatant>()!=null)
                {
                    audioController.PlayAudio(MonsterAudioType.MeleeAttackHit);
                    if (particle == null)
                    {
                        particle = particleController.GetParticle(MonsterParticleType.MeleeHit);
                    }
                    particle.transform.position = other.transform.position;
                    particle.Play();
                    SetAndAttack(other.transform);
                }
            }
        }
        private void SetAndAttack(Transform otherTransform)
        {
            CombatPayload payload = new();
            payload.Type = data.combatType;
            payload.Attacker = transform;
            payload.Defender = otherTransform;
            payload.AttackDirection = Vector3.zero;
            payload.AttackStartPosition = transform.position;
            payload.AttackPosition = otherTransform.position;
            payload.StatusEffectName = StatusEffectName.WeakRigidity;
            payload.statusEffectduration = 0.3f;
            payload.Damage = data.damage;
            Attack(payload);
        }
    }
}
