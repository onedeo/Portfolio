using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class ProjectileBase : MonoBehaviour
    {
        protected ProjectileAttackData projectileData;
        protected MonsterProjectileAttack spawner;
        protected SphereCollider collider;
        private bool isActivated;

        private void FixedUpdate()
        {
            if (isActivated)
                transform.Translate(Vector3.forward * projectileData.projectileSpeed * Time.deltaTime);
        }
        private void OnTriggerEnter(Collider other)
        {
            if (other.CompareTag("Wall") || other.CompareTag("Player"))
                Explode();

            if (other.CompareTag("Player"))
                spawner.SetAndAttack(other.transform);
        }

        public void SetInitialData(ProjectileAttackData projectileData)
        {
            this.projectileData = projectileData;
            collider = GetComponent<SphereCollider>();
            if (collider == null)
                Debug.LogFormat("Projectile {0} Has No Collider : {0}", projectileData.name);
            collider.enabled = true;
            collider.isTrigger = true;
        }

        public void Fire()
        {
            if(projectileData==null)
            {
                Debug.LogFormat("{0} Has Not Initialized ProjectileAttack : {0}, ProjectileAttack" + transform.name);
                return;
            }
            collider.enabled = true;
            isActivated = true;
            transform.localScale = Vector3.one;
            transform.position = spawner.transform.position;
            transform.rotation = spawner.transform.rotation;

            StartCoroutine(OnDurationEnd());
        }
        private void Explode()
        {
            spawner.Explode(transform);
            transform.localScale = Vector3.zero;
            collider.enabled = false;
            isActivated = false;
        }
        private IEnumerator OnDurationEnd()
        {
            yield return new WaitForSeconds(projectileData.duration);
            if(isActivated) Explode();
        }
    }
}