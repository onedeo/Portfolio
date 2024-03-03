using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class WizardSkeletonBT : MonsterBehaviourTree
    {
        private void Start()
        {
            Select attackSelect = new(new List<Node>
            {
                new SeqFleeSkill(),
                new SeqProjectileAttack(),
            });
            Select movementSelect = new(new List<Node>
            {
                new SeqOvertravel(),
                new SeqChasePlayer(),
                new SeqPatrol(),
            });
            Select noDetectSelect = new(new List<Node>
            {
                new SeqReturnSpawnPosition(),
                new SeqNoDetection(),
            });

            Select allSequence = new(new List<Node>
            {
                attackSelect,
                movementSelect,
                noDetectSelect,
            });

            Sequence wizardSkeletonNodes = new(new List<Node>
            {
                new ActionUpdateData(),
                allSequence,
            });

            SetupTree(new Repeater(wizardSkeletonNodes));
        }
    }
}
