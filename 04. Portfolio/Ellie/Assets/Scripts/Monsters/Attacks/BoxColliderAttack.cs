using System.Collections;
using Assets.Scripts.Monsters.AbstractClass;
using Channels.Combat;
using UnityEngine;
using Assets.Scripts.Combat;

namespace Assets.Scripts.Monsters.Attacks
{
    public class BoxColliderAttack : AbstractAttack
    {
        private BoxCollider collider;
        private MonsterAttackData attackData;
        private ParticleSystem particle;

        public override void InitializeBoxCollider(MonsterAttackData data)
        {
            attackData = data;
            InitializedBase(data);

            if (collider == null)
            {
                collider = gameObject.AddComponent<BoxCollider>();
                collider.isTrigger = true;
            }

            collider.size = data.size;
            gameObject.transform.localPosition = data.offset;
            collider.enabled = false;

            if (audioController == null)
                audioController = transform.parent.GetComponent<MonsterAudioController>();
            if (particleController == null)
                particleController = transform.parent.GetComponent<MonsterParticleController>();
        }

        public override void ActivateAttack()
        {
            collider.enabled = true;
            StartCoroutine(DisableCollider());
        }

        private IEnumerator DisableCollider()
        {
            yield return new WaitForSeconds(durationTime);
            collider.enabled = false;
        }

        private void OnTriggerEnter(Collider other)
        {
            if (other.CompareTag("Player"))
            {
                if (other.gameObject.GetComponent<ICombatant>() != null)
                {
                    audioController.PlayAudio(MonsterAudioType.MeleeAttackHit);
                    if (particle == null)
                    {
                        particle = particleController.GetParticle(MonsterParticleType.MeleeHit);
                    }
                    particle.transform.position = other.transform.position;
                    particle.Play();
                    SetAndAttack(attackData, other.transform);
                }
            }
        }

        private void SetAndAttack(MonsterAttackData data, Transform otherTransform)
        {
            CombatPayload payload = new();
            payload.Type = data.combatType;
            payload.Attacker = transform;
            payload.Defender = otherTransform;
            payload.AttackDirection = Vector3.zero;
            payload.AttackStartPosition = transform.position;
            payload.AttackPosition = otherTransform.position;
            payload.StatusEffectName = StatusEffects.StatusEffectName.WeakRigidity;
            payload.statusEffectduration = 0.3f;
            payload.Damage = (int)data.attackValue;
            Attack(payload);
        }

    }
}
