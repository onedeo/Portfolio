using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqFleeSkill : Sequence
    {
        public SeqFleeSkill()
        {
            FleeSkillData fleeData = tree.GetMonsterData<FleeSkillData>(MonsterData.Flee);

            List<Node> children = new()
            {
                new ActionSkillUseable(fleeData.interval, fleeData.attackableDistance),
                new ActionPlayAudio(MonsterAudioType.Move2),
                new ActionPlayAnimation(AnimationType.FLEE),
                new ActionHold(fleeData.animationHold),
                new ActionExecuteAttack(MonsterSkill.Flee),
                new ActionHold(fleeData.duration-fleeData.animationHold),
            };

            SetChildren(children);
        }
    }
}