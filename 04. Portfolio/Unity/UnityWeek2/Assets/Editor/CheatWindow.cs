using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEditor;
using UnityEditor.SceneManagement;


public class CheatWindow : EditorWindow
{
    /*
     * ����� MonoBehaviou���� EidtorWindow�� ����
     */

    string[] cheatList = new string[]
    {
        "ġƮ",                   // : 0
        "��� ����" ,       // : 1
        "����Ʈ ����",   // : 2
    };

    static int selectedIndex = 0;

    int getInt = 0;
    string getString = "";

    [MenuItem("Menu2023/CheatMenu/ġƮ ���â",false, 0)]
    static public void OpenCheatWindow()
    {
        CheatWindow getWindow = EditorWindow.GetWindow<CheatWindow>(false, "Cheat Window", true);
    }

    private void OnGUI()
    {
        GUILayout.Space(10f);
        int getIndex = EditorGUILayout.Popup(selectedIndex, cheatList, GUILayout.MaxWidth(200f));
        if (getIndex != selectedIndex)
            selectedIndex = getIndex;

        string cheatText = "";
        GUILayout.BeginHorizontal(GUILayout.MaxWidth(300f)); //Begin�� ������ End�� �� �־�� �Ѵ�.
        
        switch(selectedIndex)
        {
            case 0:
                GUILayout.Label("ġƮŰ �Է�", GUILayout.Width(70f));
                getString = EditorGUILayout.TextField(getString,GUILayout.Width(200));
                cheatText = string.Format("ġƮŰ : {0}", getString);
                break;
            case 1:
                GUILayout.Label("���", GUILayout.Width(70f));
                getString = EditorGUILayout.TextField(getInt.ToString(), GUILayout.Width(100f));
                int.TryParse(getString, out getInt);  //���ڿ��� int������ ����
                cheatText = string.Format("��� : {0}", getInt);
                break;
            case 2:
                GUILayout.Label("����Ʈ", GUILayout.Width(70f));
                getString = EditorGUILayout.TextField(getInt.ToString(), GUILayout.Width(100f));
                int.TryParse(getString, out getInt);  //���ڿ��� int������ ����
                cheatText = string.Format("����Ʈ : {0}", getInt);
                break;
        }    
        GUILayout.EndHorizontal();

        GUILayout.Space(20f);
        GUILayout.BeginHorizontal(GUILayout.MaxWidth(800f)); //Begin�� ������ End�� �� �־�� �Ѵ�.
        {
            GUILayout.BeginVertical(GUILayout.MaxWidth(300f));
            {
                GUILayout.BeginHorizontal(GUILayout.MaxWidth(300f));
                {
                    if (GUILayout.Button("\n����\n", GUILayout.Width(100f)))
                    {
                        if(EditorApplication.isPlaying&&EditorSceneManager.GetActiveScene().name=="Title")
                        {
                            getInt = 0;
                            getString = "";
                            // : To Do ���� �۵��Ǵ� �ڵ�
                            Debug.Log(cheatText);

                        }
                    }
                }
                GUILayout.EndHorizontal();


                GUILayout.BeginHorizontal(GUILayout.MaxWidth(300f));
                {
                    if (GUILayout.Button("\n��׶���\n����\n", GUILayout.Width(100f)))
                    {
                        Application.runInBackground = true; //focus(�ٸ� â�� Ŭ���ϸ�)�� �ٸ� ������ ������ ����
                    }
                    if (GUILayout.Button("\n��׶���\n����\n", GUILayout.Width(100f)))
                    {
                        Application.runInBackground = false; //focus(�ٸ� â�� Ŭ���ϸ�)�� �ٸ� ������ ������ �̽���
                    }
                }
                GUILayout.EndHorizontal();
            }
            GUILayout.EndVertical();


        }


        GUILayout.EndHorizontal();


    }

}
