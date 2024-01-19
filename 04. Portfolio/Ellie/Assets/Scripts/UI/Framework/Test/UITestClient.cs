using System;
using Assets.Scripts.ActionData.Monster;
using Assets.Scripts.Data.ActionData.Player;
using Assets.Scripts.Managers;
using Assets.Scripts.UI.Framework.Popup;
using Assets.Scripts.UI.Item;
using Assets.Scripts.UI.Monster;
using Assets.Scripts.UI.Player;
using Assets.Scripts.UI.Status;
using Assets.Scripts.Utils;
using Channels.Components;
using Channels.Type;
using UnityEngine;

namespace Assets.Scripts.UI.Framework
{
    public class UITestClient : MonoBehaviour
    {
        private const string UIButtonCanvas = "ButtonCanvas";
        private const string UIHealthAndStamina = "Player/HealthAndStamina";
        private const string UIStoneInven = "Item/StoneInven";
        private const string UIItemInven = "Item/ItemInven";
        private const string UIStatusCanvas = "Player/StatusCanvas";
        private const string UIMonsterCanvas = "Monster/MonsterCanvas";
        private const string UIMonsterBillboard = "Monster/MonsterBillboard";

        [SerializeField] private Transform billBoardPosition;
        [SerializeField] private PlayerHealthData healthData;
        [SerializeField] private StaminaData staminaData;
        [SerializeField] private MonsterHealthData monsterHealthData;
        [SerializeField] private int damage = 1;

        private UIStatusBar statusBar;
        private readonly MonsterDataContainer canvasContainer = new MonsterDataContainer();
        private readonly MonsterDataContainer billboardContainer = new MonsterDataContainer();

        private TicketMachine ticketMachine;

        private void Awake()
        {
            healthData.InitHealth();
            monsterHealthData.InitHealth();
            staminaData.InitStamina();

            canvasContainer.MaxHp = 45;
            canvasContainer.PrevHp = 45;
            canvasContainer.CurrentHp.Value = 45;
            canvasContainer.Name = "I'm Canvas";

            billboardContainer.MaxHp = 45;
            billboardContainer.PrevHp = 45;
            billboardContainer.CurrentHp.Value = 45;
            billboardContainer.Name = "I'm billboard";

            ticketMachine = gameObject.GetOrAddComponent<TicketMachine>();
            ticketMachine.AddTickets(ChannelType.UI);
        }

        private void OnEnable()
        {
            InputManager.Instance.keyAction -= OnKeyAction;
            InputManager.Instance.keyAction += OnKeyAction;
        }

        private const string PrefixExclamationPath = "UI/Inven/Exclamation/";
        private const string ExclamationGray = "Exclamation_Gray";
        private const string ExclamationRed = "Exclamation_Red";

        private void OnKeyAction()
        {
        }

        private void Start()
        {
            UIManager.Instance.MakePopup<UIPopupButton>(UIButtonCanvas);
            UIManager.Instance.MakeStatic<UIHealthAndStamina>(UIHealthAndStamina);
            UIManager.Instance.MakeStatic<UIStoneInven>(UIStoneInven);
            UIManager.Instance.MakeStatic<UIItemInven>(UIItemInven);
            statusBar = UIManager.Instance.MakeStatic<UIStatusBar>(UIStatusCanvas);

            var canvas = UIManager.Instance.MakeStatic<UIMonsterCanvas>(UIMonsterCanvas);
            canvas.InitData(canvasContainer);

            var billboard = UIManager.Instance.MakeStatic<UIMonsterBillboard>(billBoardPosition, UIMonsterBillboard);
            billboard.scaleFactor = 0.003f;
            billboard.InitBillboard(billBoardPosition);
            billboard.InitData(billboardContainer);
        }

        private void OnGUI()
        {
            float w = Screen.width;
            float h = Screen.height;
            if (GUI.Button(new Rect(10, h - 30, 100, 20), "attack player"))
            {
                int val = Math.Clamp(healthData.CurrentHealth.Value - damage, 0, healthData.MaxHealth);
                healthData.CurrentHealth.Value = val;
            }

            if (GUI.Button(new Rect(10, h - 60, 100, 20), "heal player"))
            {
                int val = Math.Clamp(healthData.CurrentHealth.Value + damage, 0, healthData.MaxHealth);
                healthData.CurrentHealth.Value = val;
            }

            //if (GUI.Button(new Rect(10, h - 90, 100, 20), "use stamina"))
            //{
            //    int val = Math.Clamp(staminaData.CurrentStamina.Value - staminaCost, 0, staminaData.MaxStamina);
            //    staminaData.CurrentStamina.Value = val;
            //}

            //if (GUI.Button(new Rect(10, h - 120, 100, 20), "restore stamina"))
            //{
            //    int val = Math.Clamp(staminaData.CurrentStamina.Value + staminaCost, 0, staminaData.MaxStamina);
            //    staminaData.CurrentStamina.Value = val;
            //}

            if (GUI.Button(new Rect(10, h - 150, 100, 20), "add status"))
            {
                statusBar.AddStatus();
            }

            if (GUI.Button(new Rect(10, h - 180, 100, 20), "remove status"))
            {
                statusBar.RemoveStatus();
            }

            if (GUI.Button(new Rect(300, h - 30, 100, 20), "attack boss monster"))
            {
                int val = Math.Clamp(canvasContainer.CurrentHp.Value - damage, 0, canvasContainer.MaxHp);
                canvasContainer.CurrentHp.Value = val;
            }

            if (GUI.Button(new Rect(300, h - 60, 100, 20), "heal boss monster"))
            {
                int val = Math.Clamp(canvasContainer.CurrentHp.Value + damage, 0, canvasContainer.MaxHp);
                canvasContainer.CurrentHp.Value = val;
            }

            if (GUI.Button(new Rect(300, h - 90, 100, 20), "attack billboard monster"))
            {
                int val = Math.Clamp(billboardContainer.CurrentHp.Value - damage, 0, billboardContainer.MaxHp);
                billboardContainer.CurrentHp.Value = val;
            }

            if (GUI.Button(new Rect(300, h - 120, 100, 20), "heal billboard monster"))
            {
                int val = Math.Clamp(billboardContainer.CurrentHp.Value + damage, 0, billboardContainer.MaxHp);
                billboardContainer.CurrentHp.Value = val;
            }
        }
    }
}