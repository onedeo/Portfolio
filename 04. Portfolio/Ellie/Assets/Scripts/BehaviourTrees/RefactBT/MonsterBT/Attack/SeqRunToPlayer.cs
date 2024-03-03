using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqRunToPlayer : Sequence
    {
        public SeqRunToPlayer()
        {
            RunToPlayerData runToPlayer = tree.GetMonsterData<RunToPlayerData>(MonsterData.RunToPlayer);

            List<Node> children = new()
            {
                new ActionSkillUseable(runToPlayer.interval, runToPlayer.attackableDistance),
                new ActionPlayAudio(MonsterAudioType.MoveSkill),
                new ActionPlayAnimation(AnimationType.RUN),
                new ActionRunToPlayer()
            };

            SetChildren(children);
        }
    }
}