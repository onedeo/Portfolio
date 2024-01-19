using Assets.Scripts.ActionData;

namespace Assets.Scripts.UI.Monster
{
    public class MonsterDataContainer
    {
        public int PrevHp { get; set; }
        public int MaxHp { get; set; }
        public readonly Data<int> CurrentHp = new Data<int>();

        public string Name { get; set; }
    }
}