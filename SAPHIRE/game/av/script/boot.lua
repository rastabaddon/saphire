-- ================================================================================
--  STANDARD BOOT SCRIPT
-- ================================================================================

print ("Advena Universi: The begining");


--_Video:setVideo(640,480);

--_Cfg:loadCfg ("/config/default.xml");

-- ================================================================================
--  NO GAMEMODE SHUTDOWN
-- ================================================================================
--shutDown();

--_Resource:loadAllResources("Av");

--include "ObjectMenager.lua"

--scene = _Scene:createScene(0,0,0);
--_Scene:setCurrentScene(scene);
--scene:setCameraPosition(0,5,0); --Main camera

--[[
player = Controler:createControler(Controler.PLAYER); -- With default key assign / obsluga myszy i klawiatury


bigBox = Object:createObject(Object.STATIC,"obj/bigBox.3ds");
bigBox:setPosition(10,-10,10);
scene:addObject(bigBox);


Video:setLoadingScreenShowStatus(false);

scene:setPause(false)
]]
print("WSZYSTKO JUZ POWINNO BYC ZROBIONE")

-- DODAJEMY OBIEKT

print("Tworzymy scene")
	scene = _Scene:createScene(0,0,0);
	
print("Ustawiamy scene")
	_Scene:setActiveScene(scene);
	
print("Ustawiamy kamere")
	camera = scene:createCamera(0,10,4);
	scene:setActiveCamera(camera); --???
	
--	camera:setPosition(0,0,4);
	x,y,z = camera:getPosition();
	 
	print("POS",x,y,z);
	
print("Tworzymy obiekt")

		test1 = scene:createMeshSceneNode("teren",0,0,0);  --TERAIN
		
		test2 = scene:createMeshSceneNode("marine",-50,-50,-50);  --TERAIN
		test1:setPosition(10,10,10);
				
		test3 = scene:createMeshSceneNode("test",-100,-100,-100);  --TERAIN
				
		--for x = 0, 10, 1 do
	--	    for y = 0, 10, 1 do
		--      for z = 0, 10, 1 do
   --           test2 = scene:createMeshSceneNode("test",5*x,5*y,5*z);
   --          test2:setPosition(5*x,5*y,5*z);
   --       end
  --     end
  --  end
		
		
					
print("Ustawiamy obiekt")
	--testObject:setPosition(10,-10,10);
	
print("Dodajemy do sceny obiekt")
	--scene:addObject(testObject);
	

print("Bindujemy eventy")

tt = string.dump(function() print("test") end)
print(tt)
test = loadstring( tt )
--test()

_Event:bind("KEYBOARD",function(event) 
    if(event.keyCode=='27' and event.keyPressed ) then
      print("Shutdown");
      shutDown();
    end
    
    print(event.eventType,event.eventSubType,event.keyCode,event.keyPressed)
  
  end)


