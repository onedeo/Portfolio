using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class NormalSkeletonBT : MonsterBehaviourTree
    {
        private void Start()
        {
            // Monster Attack Sequences
            Select attackSelect = new(new List<Node>
            {
                new SeqRunToPlayer(),
                new SeqMeleeAttack()
            });

            // Monster Cant Attack, But Can Move Sequences
            Select movementSelect = new(new List<Node>
            {
                new SeqOvertravel(),
                new SeqNearPlayer(),
                new SeqChasePlayer(),
                new SeqPatrol(),
            });

            // Monster Cant detect player Sequences
            Select noDetectSelect = new(new List<Node>
            {
                new SeqReturnSpawnPosition(),
                new SeqNoDetection(),
            });

            // Combine All Sequences      
            Select allSequence = new(new List<Node>
            {
                attackSelect,
                movementSelect,
                noDetectSelect,
            });

            // Combine Update Data
            Sequence normalSkeletonNodes = new(new List<Node>
            {
                new ActionUpdateData(),
                allSequence,
            });

            SetupTree(new Repeater(normalSkeletonNodes));
        }
    }
}