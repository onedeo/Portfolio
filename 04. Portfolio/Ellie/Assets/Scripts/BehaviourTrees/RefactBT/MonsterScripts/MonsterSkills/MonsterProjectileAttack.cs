using Assets.Scripts.Managers;
using Assets.Scripts.StatusEffects;
using Channels.Combat;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterProjectileAttack : MonsterAttackBase
    {
        private const string path = "Prefabs/Monster/Projectiles/";

        private ProjectileAttackData projectileData;
        private GameObject projectileObj;
        private ProjectileBase projectile;

        protected override void Awake()
        {
            base.Awake();          

            string finalPath = path + projectileData.name;
            projectileObj = Instantiate(ResourceManager.Instance.LoadExternResource<GameObject>(finalPath), transform);
            if (projectileObj == null)
                Debug.LogFormat("{0} Trying To Instanciate {1} But No Prefab On {2} : {0}, {1}", transform.name, projectileData.name, path);
            else
                projectile = projectileObj.GetComponent<ProjectileBase>();
        }
        public void SetInitialData(ProjectileAttackData projectileData)
        {
            this.projectileData = projectileData;
        }
        public override void ExecuteAttack()
        {
            if (projectileData == null)
                Debug.LogFormat("{0} Has Not Initialized {1} : {0}, {1}" + transform.name, projectileData.name);
            else projectile.Fire();
        }
        public void Explode(Transform transform)
        {
            particleController.PlayParticle(MonsterParticleType.ProjectileHit, transform);
            audioController.PlayAudio(MonsterAudioType.ProjectileHit, transform);
        }
        public void SetAndAttack(Transform otherTransform)
        {
            CombatPayload payload = new();
            payload.Type = projectileData.combatType;
            payload.Attacker = transform;
            payload.Defender = otherTransform;
            payload.AttackDirection = Vector3.zero;
            payload.AttackStartPosition = transform.position;
            payload.AttackPosition = otherTransform.position;
            payload.StatusEffectName = StatusEffectName.Burn;
            payload.statusEffectduration = 3.0f;
            payload.Damage = (int)projectileData.damage;
            Attack(payload);
        }
    }
}