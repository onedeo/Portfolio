using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEditor;  // Editor 메뉴 사용
using UnityEditor.SceneManagement; //Scene 사용

public class Menu2023: MonoBehaviour
{
    [MenuItem("Menu2023/Clear PlayerPrefs")]
    private static void ClearAll_PlayerPrefs()
    {
        PlayerPrefs.DeleteAll();
        Debug.Log("ClearAll_PlayerPrefs");
    }
    [MenuItem("Menu2023/SubMenu/Select")]
    private static void SubMenu_Select()
    {
        Debug.Log("Sub Menu 1 - Select");
    }

    /*
    % :  - ctrl
    # - shift
    & - alt
    */

    [MenuItem("Menu2023/SubMenu/HotKey Test1 %#[")]
    private static void SubMenu_HotKey()
    {
        Debug.Log("HotKey Test : Ctrl+Shift+[");
    }

    //우클릭 했을 때 실행
    //게임이 실행되지 않은 상태에서 '만' 실행
    [MenuItem("Assets/Load Selected Scene")]
    private static void LoadSelectedScene()
    {
        var selected = Selection.activeObject;
        if (EditorApplication.isPlaying)
        {
            EditorSceneManager.LoadScene(AssetDatabase.GetAssetPath(selected));
        }
        else//게임이 실행되지 않은 상태에서 '만' 실행
            EditorSceneManager.OpenScene(AssetDatabase.GetAssetPath(selected));
    }

}
