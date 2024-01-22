using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEditor;
using UnityEditor.SceneManagement;


public class CheatWindow : EditorWindow
{
    /*
     * 상속을 MonoBehaviou에서 EidtorWindow로 변경
     */

    string[] cheatList = new string[]
    {
        "치트",                   // : 0
        "골드 생성" ,       // : 1
        "포인트 생성",   // : 2
    };

    static int selectedIndex = 0;

    int getInt = 0;
    string getString = "";

    [MenuItem("Menu2023/CheatMenu/치트 명령창",false, 0)]
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
        GUILayout.BeginHorizontal(GUILayout.MaxWidth(300f)); //Begin이 있으면 End가 꼭 있어야 한다.
        
        switch(selectedIndex)
        {
            case 0:
                GUILayout.Label("치트키 입력", GUILayout.Width(70f));
                getString = EditorGUILayout.TextField(getString,GUILayout.Width(200));
                cheatText = string.Format("치트키 : {0}", getString);
                break;
            case 1:
                GUILayout.Label("골드", GUILayout.Width(70f));
                getString = EditorGUILayout.TextField(getInt.ToString(), GUILayout.Width(100f));
                int.TryParse(getString, out getInt);  //문자열을 int형으로 변경
                cheatText = string.Format("골드 : {0}", getInt);
                break;
            case 2:
                GUILayout.Label("포인트", GUILayout.Width(70f));
                getString = EditorGUILayout.TextField(getInt.ToString(), GUILayout.Width(100f));
                int.TryParse(getString, out getInt);  //문자열을 int형으로 변경
                cheatText = string.Format("포인트 : {0}", getInt);
                break;
        }    
        GUILayout.EndHorizontal();

        GUILayout.Space(20f);
        GUILayout.BeginHorizontal(GUILayout.MaxWidth(800f)); //Begin이 있으면 End가 꼭 있어야 한다.
        {
            GUILayout.BeginVertical(GUILayout.MaxWidth(300f));
            {
                GUILayout.BeginHorizontal(GUILayout.MaxWidth(300f));
                {
                    if (GUILayout.Button("\n적용\n", GUILayout.Width(100f)))
                    {
                        if(EditorApplication.isPlaying&&EditorSceneManager.GetActiveScene().name=="Title")
                        {
                            getInt = 0;
                            getString = "";
                            // : To Do 실제 작동되는 코드
                            Debug.Log(cheatText);

                        }
                    }
                }
                GUILayout.EndHorizontal();


                GUILayout.BeginHorizontal(GUILayout.MaxWidth(300f));
                {
                    if (GUILayout.Button("\n백그라운드\n실행\n", GUILayout.Width(100f)))
                    {
                        Application.runInBackground = true; //focus(다른 창을 클릭하면)가 다른 곳으로 빠져도 실행
                    }
                    if (GUILayout.Button("\n백그라운드\n안함\n", GUILayout.Width(100f)))
                    {
                        Application.runInBackground = false; //focus(다른 창을 클릭하면)가 다른 곳으로 빠져도 미실행
                    }
                }
                GUILayout.EndHorizontal();
            }
            GUILayout.EndVertical();


        }


        GUILayout.EndHorizontal();


    }

}
