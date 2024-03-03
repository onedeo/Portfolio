using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqWeaponAttack : Sequence
    {
        public SeqWeaponAttack()
        {
            WeaponAttackData weaponData = tree.GetMonsterData<WeaponAttackData>(MonsterData.Weapon);

            List<Node> children = new()
            {
                new ActionSkillUseable(weaponData.interval, weaponData.attackableDistance),
                new ActionStop(),
                new ActionPlayAudio(MonsterAudioType.WeaponAttackCast),
                new ActionPlayAnimation(AnimationType.WEAPON),
                new ActionHold(weaponData.animationHold),
                new ActionPlayParticle(MonsterParticleType.WeaponSwing),
                new ActionPlayAudio(MonsterAudioType.WeaponAttackPerform),
                new ActionExecuteAttack(MonsterSkill.Weapon),
                new ActionHold(weaponData.duration-weaponData.animationHold),
                new ActionSetAgent(tree.GetBTData<Vector3>(BTData.v3PlayerPosition)),
            };

            SetChildren(children);
        }

    }
}
