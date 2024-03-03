using System.Collections;
using Assets.Scripts.StatusEffects;
using Channels.Combat;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterWeaponeAttack : MonsterAttackBase
    {
        private WeaponAttackData data;
        private GameObject target;

        protected override void Awake()
        {
            base.Awake();
            target = GameObject.Find("Player");
        }
        public void SetInitialData(WeaponAttackData WeaponData)
        {
            data = WeaponData;
        }    
        public override void ExecuteAttack()
        {
            StartCoroutine(AttackFanshape());
        }
        public IEnumerator AttackFanshape()
        {
            float accumTime = 0.0f;
            while (accumTime <= data.duration)
            {
                if (CaculateDotProduct())
                {
                    if (target.CompareTag("Player"))
                    {
                        audioController.PlayAudio(MonsterAudioType.WeaponAttackHit);
                        particleController.PlayParticle(MonsterParticleType.WeaponHit, target.transform);

                        SetAndAttack(data, target.transform);
                        break;
                    }
                }
                accumTime += Time.deltaTime;
                yield return null;
            }
        }
        private bool CaculateDotProduct()
        {
            Vector3 interV = target.transform.position - transform.position;

            float dot = Vector3.Dot(interV.normalized, transform.forward.normalized);
            float theta = Mathf.Acos(dot);
            float degree = Mathf.Rad2Deg * theta;

            if (degree <= data.angle / 2.0f)
            {
                interV.y = 0;
                if (interV.sqrMagnitude <= data.radius * data.radius)
                {
                    return true;
                }
            }

            return false;
        }
        private void SetAndAttack(WeaponAttackData data, Transform otherTransform)
        {
            CombatPayload payload = new();
            payload.Type = data.combatType;
            payload.Attacker = transform;
            payload.Defender = otherTransform;
            payload.AttackDirection = Vector3.zero;
            payload.AttackStartPosition = transform.position;
            payload.AttackPosition = otherTransform.position;
            payload.StatusEffectName = StatusEffectName.WeakRigidity;
            payload.statusEffectduration = 0.5f;
            payload.Damage = data.damage;
            Attack(payload);
        }
    }
}