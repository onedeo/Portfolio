

/*
1. 어소트 인강 33화 18분
		총알 Enemy collision 작업하고 있었음

*/

//====Player
/*
<variable>
// stat
int fSpeed
float fOCGSpeed >> ratio of change speed
float fRetreatSpeed >> ratio of change speed

Vec2 vCenter

//for ocg
int iOCGCnt
Vec2 pOCGPoint[1000]
bool bEnemyInOCGPoints;

//for ocd
DIRECTION eDirStart
DIRECTION eDirFin
bool bClockwise


// toss clockwise, ocgpoints, add/delete prv or nxt direction
<function>
>>player movement
bool isPlayerMoveAble() -> check with isPlayerSafe and move
void PlayerRetreat()-> player retreat by unpress spacekey

>>player occupying
void CollectOCGPoints() -> collect ocgpoints for add on ocd
void DeleteOCGPoint() -> when player go back

>>player finish occupying and toss information to ocd class
void ConfigEnemeyInOCGPoint() -> check enemy is in the ocgpoints
void ConfigClockwise() -> check clockwise or not
>> 1. check if enemy is in ocgpoints
>> 2. using start and fin direction, get clockwise
>> 3. toss both to area and area will delete and add

//get and sets
bool getEnemyInOCGPoints()
>> : for tossing info to OCD
bool getClockwise()
int getOCGCnt()
Vec2 getOCGPoint(int i)
<< : for tossing info to OCD
*/

//====Enemy
/*
<variable>
int fSpeed
Vec2 vCenter
Vec2 vVecotr

<function>
void ActivateEnemySkill1()
void ActivateEnemySkill2()
void ActivateEnemySkill3()

*/

/*
====Occupied
<variable>
OCDPoint ocdAddStart
OCDPoint ocdDeleteStart
OCDPoint ocdDeleteEnd

<function>
void addOCPointsToOCDPoints(bool _isclockwise)
void deleteOCPointsToOCDPoints(bool _isclockwise)
>> do we need boolean for clockwise and add/delete direction??
*/

/*
====Skill
<variable>
Vec2 Vector




*/


//====Structure
/*
struct Vec2
{
// use assort vector

}
struct OCDPoint
{
	<variable>
	POINT point
	OCDPoint* nxt
	OCDpoint* prv

	<function>
	public:
	void InsertNxt(OCDPoint _OCDPoint)
	void InsertNxt(Vec2 _ve2)
	void InsertPrv(OCDPoint _OCDPoint)
	void InsertPrv(Vec2 _ve2)
	void DeleteNxt(OCDPoint _OCDPoint)
	void DeleteNxt(Vec2 _ve2)
	void DeletePrv(OCDPoint _OCDPoint)
	void DeletePrv(Vec2 _ve2)
}
struct OCDPlist
{
	OCDPoint* head
	OCDPoint* crnt

	public:
	void 
}
>> insert/delete on next OCDPoint or Vec2(make new OCDPoint and insert)
>> maybe add this OCDPoint and OCDPlist on class and make functions on class. 

*/

//====General Functions
/*
<variable>

<function>
*/

//====Manager
/*
<variable>
int iPlayerLife
PLAYER_STATE iPlayerState
bool bIsPlayerSafe

<function>
bool isPlayerSafe(POINT center) -> check if player is safe on the center
*/

//====Enum
/*
enum class PLAYER_STATE { OCCUPIED, OCCUPYING, READY_OCD, ENEMY_CLSN}
enum class DIRECTION {UP, DOWN, RIGHT, LEFT}
enum class SKILL
{
// general
SLOW, STUN, KILL
//pikachu
PIKACHU_FLASH
//bulasour

//ghost

....
}
*/