using System.Collections;
using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterFleeSkill : MonsterAttackBase
    {
        private const int constMaxAttempts = 5;
        private FleeSkillData fleeData;
        private MonsterStatData statData;
        private NavMeshAgent agent;

        private Vector3 directionVector;
        private Vector3 runAwayVector;
        private Vector3 fleeVector;
        private int attemptFlee;
        private GameObject player;

        protected override void Awake()
        {
            base.Awake();
            player = GameObject.Find("Player");
            agent = GetComponent<NavMeshAgent>();

        }
        public void SetInitialData(MonsterStatData statData, FleeSkillData fleeData)
        {
            this.statData = statData;
            this.fleeData = fleeData;
        }
        public override void ExecuteAttack()
        {
            if(statData==null||fleeData==null)
            {
                Debug.LogFormat("{0} Has Not Initialized WeaponAttack : {0}, WeaponAttack" + transform.name);
                return;
            }
            attemptFlee = 0;
            directionVector = player.transform.position - transform.position;
            directionVector.y = 0.0f;
            runAwayVector = directionVector.normalized * -fleeData.fleeDistance;
            fleeVector = transform.position + runAwayVector;

            // Check Walls
            RaycastHit hit;
            do
            {
                bool isHittedWall = true;
                if (Physics.Raycast
                    (transform.position, runAwayVector.normalized, out hit, fleeData.fleeDistance))
                {
                    if (hit.collider.tag == "Wall")
                    {
                        runAwayVector = Random.onUnitSphere;
                    }
                    else isHittedWall = false;
                }
                else isHittedWall = false;

                // Check NavMesh
                if (!isHittedWall)
                {
                    NavMeshHit navMeshHit;
                    if (NavMesh.SamplePosition(fleeVector, out navMeshHit, 1.0f, NavMesh.AllAreas))
                    {
                        // Found Runaway Point
                        agent.destination = navMeshHit.position;
                        agent.speed = fleeData.fleeSpeed;
                        StartCoroutine(FinishUsingFlee());
                        break;
                    }
                }

                attemptFlee++;
            } while (attemptFlee < constMaxAttempts);
        }
        private IEnumerator FinishUsingFlee()
        {
            yield return new WaitForSeconds(fleeData.duration - fleeData.animationHold);
            agent.speed = statData.speed;
        }
    }
}