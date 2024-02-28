using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqProjectileAttack : Sequence
    {
        public SeqProjectileAttack()
        {
            ProjectileAttackData data = tree.GetMonsterData<ProjectileAttackData>(MonsterData.Projectile);

            List<Node> children = new()
            {
                new ActionSkillUseable(data.interval, data.attackableDistance),
                new ActionStop(),
                new ActionPlayAudio(MonsterAudioType.ProjectileAttack, true, false),
                new ActionPlayAnimation(AnimationType.PROJECTILE_CAST,true),
                new ActionPlayAnimation(AnimationType.PROJECTILE_FIRE, false),
                new ActionHold(data.animationHold),
                new ActionPlayAudio(MonsterAudioType.ProjectileFire),
                new ActionExecuteAttack(MonsterSkill.Projectile),
                new ActionSetAgent(tree.GetBTData<Vector3>(BTData.v3PlayerPosition)),
            };

            SetChildren(children);
        }
    }
}