using System.Collections;
using Assets.Scripts.Managers;

namespace Scripts.BehaviourTrees.Monster
{
    public class WizardSkeleton : MonsterBase
    {
        private enum ParsingData
        {
            MonsterStat = 1902,
            Flee = 2008,
            ProjectileAttack = 2009,
        }

        private FleeSkillData fleeData;
        private ProjectileAttackData projectileData;

        protected override void Start()
        {
            base.Start();
            StartCoroutine(InitParsingData());
        } 
        private IEnumerator InitParsingData()
        {
            yield return DataManager.Instance.CheckIsParseDone();

            monsterStat = DataManager.Instance.GetIndexData<MonsterStatData, MonsterStatDataParsingInfo>((int)ParsingData.MonsterStat);
            fleeData = DataManager.Instance.GetIndexData<FleeSkillData, MonsterAttackDataparsingInfo>((int)ParsingData.Flee);
            projectileData = DataManager.Instance.GetIndexData<ProjectileAttackData, MonsterAttackDataparsingInfo>((int)ParsingData.ProjectileAttack);

            SetSkills();
            SetMonsterData(monsterStat);

            tree.AddMonsterData<MonsterStatData>(MonsterData.MonsterStat, monsterStat);
            tree.AddMonsterData<FleeSkillData>(MonsterData.Melee, fleeData);
            tree.AddMonsterData<ProjectileAttackData>(MonsterData.RunToPlayer, projectileData);
        }

        private void SetSkills()
        {
            MonsterFleeSkill fleeAttack = new();
            fleeAttack.SetInitialData(monsterStat, fleeData);
            AddAttack(MonsterSkill.Flee, fleeAttack);

            MonsterProjectileAttack projectileAttack = new();
            projectileAttack.SetInitialData(projectileData);
            AddAttack(MonsterSkill.Projectile, projectileAttack);
        }
    }
}