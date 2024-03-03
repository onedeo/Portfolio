using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class GuildGuardSkeletonBT : MonsterBehaviourTree
    {
        private void Start()
        {
            Select attackSelect = new(new List<Node>
            {
                new SeqRunToPlayer(),
                new SeqWeaponAttack(),
                new SeqMeleeAttack()
            });
            Select movementSelect = new(new List<Node>
            {
                new SeqOvertravel(),
                new SeqNearPlayer(),
                new SeqChasePlayer(),
                new SeqPatrol(),
            });
            Select noDetectSelect = new(new List<Node>
            {
                new SeqReturnSpawnPosition(),
                new SeqNoDetection(),
            });

            Sequence allSequence = new(new List<Node>
            {
                attackSelect,
                movementSelect,
                noDetectSelect,
            });

            Sequence guildguardSkeletonNodes = new(new List<Node>
            {
                new ActionUpdateData(),
                allSequence,
            });

            SetupTree(new Repeater(guildguardSkeletonNodes));
        }
    }
}