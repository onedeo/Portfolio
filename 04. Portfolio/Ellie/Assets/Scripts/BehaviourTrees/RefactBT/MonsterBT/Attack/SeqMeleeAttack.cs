using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqMeleeAttack : Sequence
    {
        public SeqMeleeAttack()
        {
            MeleeAttackData meleeAttack = tree.GetMonsterData<MeleeAttackData>(MonsterData.Melee);

            List<Node> children = new()
            {
                new ActionSkillUseable(meleeAttack.interval, meleeAttack.attackableDistance),
                new ActionStop(),
                new ActionPlayAudio(MonsterAudioType.MeleeAttack,true, false),
                new ActionPlayAnimation(AnimationType.MELEE),
                new ActionHold(meleeAttack.animationHold),
                new ActionPlayParticle(MonsterParticleType.MeleeAttack),
                new ActionExecuteAttack(MonsterSkill.Melee),
                new ActionHold(meleeAttack.duration-meleeAttack.animationHold),
                new ActionSetAgent(tree.GetBTData<Vector3>(BTData.v3PlayerPosition)),
            };

            SetChildren(children);
        }
    }
}