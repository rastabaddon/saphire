
print ("Sapphire engine init");

_Video:setWindowTitle("Saphire Engine v1.3");


-- ================================================================================
--  STANDARD INCLUDE
-- ================================================================================

include "game.lua"
include "config.lua"
include "gui.lua";
include "resource.lua";

_Cfg:loadCfg("/config/default.xml");




if(_Video:setVideo(tonumber(_Cfg.Screen.Width),tonumber(_Cfg.Screen.Height))==false) then
	error("Can`t create video")
	shutDown();
end



-- ================================================================================
-- LOADING ALL RESOURCES
-- ================================================================================

--_Resource:loadAllResources("xEngine");

-- ================================================================================
-- INCLUDE GAME BOOT SCRIPT
-- ================================================================================

print ("Load boot script");
include("/script/boot.lua"); -- Load current game boot script ;-)


