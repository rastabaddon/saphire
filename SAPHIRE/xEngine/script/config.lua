-- ================================================================================
--  STANDARD CONFIG LIB
-- ================================================================================
if (_Cfg == nil) then

_Cfg = {}
-- ================================================================================
-- DEFAULT CFG
-- ================================================================================

-- ------------------------------ DEBUG SECTION -------------------------------
	_Cfg.Debug = {}
	_Cfg.Debug.Print 	= true;
	_Cfg.Debug.Info 	= true;
	_Cfg.Debug.Error 	= true;
	_Cfg.Debug.Warning 	= true;
	_Cfg.Debug.Senderror 	= true;
	_Cfg.Debug.Debugmode	= true;
-- ------------------------------ SCREEN SECTION ------------------------------
	_Cfg.Screen = {}
	_Cfg.Screen.Width 	= 800;
	_Cfg.Screen.Height 	= 600;
	_Cfg.Screen.Fullscreen 	= false;
	_Cfg.Screen.Vsync 	= false;
-- ------------------------------  SOUND SECTION  ------------------------------
	_Cfg.Sound = {}
	_Cfg.Sound.Soundcard	= 1;	
-- ------------------------------  NETWORK SECTION  ----------------------------
	_Cfg.Net = {}
	_Cfg.Net.Server		= "localhost"
	_Cfg.Net.Lastip		= "127.0.0.1"
-- ------------------------------  GAME SECTION  ------------------------------
	_Cfg.Game = {}
	_Cfg.Game.Gamemode 	= "default";
	_Cfg.Game.Bootscreen	= "xEngine/img/boot.png";
	_Cfg.Game.Botbara	= "xEngine/img/loadinga.png";
	_Cfg.Game.Botbarb	= "xEngine/img/loadingb.png";

-- ------------------------------  PLAYER SECTION  ------------------------------
	_Cfg.Player = {}
	_Cfg.Player.Username 	= "Player";


end

-- ================================================================================
-- CFG FUNCTIONS
-- ================================================================================
_Cfg.loadCfg = function(this,filename)

	print("CFG: "..tostring(this)..","..tostring(filename));
	-- cfg = _Resource:loadIniFile(filename);


end
