--[[
ObjectMenager.addCar = function (self,xml,scene)
	
		-- BODY
		car = Object:createObject(Object.CAR,"obj/"..xml.Body.Object);
		if car==false then return false; end

		car.scene = scene;
		car.cameraSnapToMy = false;
		
		car:setMass(xml.Body.Mass);
		car:addEngineConfig(xml.Engine);
		car.Config = xml;

		--CONECTORS
		for i=1,xml.Body.Connectors do	

			-- prepare data	
			if (xml['Connector'..i].Steering=="true") then
				xml['Connector'..i].Steering = true;
			else
				xml['Connector'..i].Steering = false;
			end

			if (xml['Connector'..i].Engine=="true") then
				xml['Connector'..i].Engine = true;
			else
				xml['Connector'..i].Engine = false;
			end

			if (xml['Connector'..i].Break=="true") then
				xml['Connector'..i].Break = true;
			else
				xml['Connector'..i].Break = false;
			end

			if (xml['Connector'..i].Handbreak=="true") then
				xml['Connector'..i].Handbreak = true;
			else
				xml['Connector'..i].Handbreak = false;
			end

			car:wheelSlotPosition(i,xml['Connector'..i].X,xml['Connector'..i].Y,xml['Connector'..i].Z,xml['Connector'..i].Steering,"obj/"..xml['Connector'..i].Object);
		end

		for i=1,xml.Body.Connectors do		
			wheel = Object:createObject(Object.DYNAMIC,"obj/"..xml['Wheel'..i].Object);
			wheel:setMass(0);
			wheel:setPosition(0,0,0);
			scene:addObject(wheel);
			car:addWheels(i,wheel);
		end


		car.onKey = function(self,who,event)
			--print ("CHAR A ("..tostring(event.Char)..") ["..tostring(event.PressedDown).."]")
		
		
			-- 1,3 TYL
			-- 2,4 przod
			if(event.Char==48 and event.PressedDown==true ) then
				
				if self.cameraSnapToMy == false then
					self.scene:snapCameraTo(self)
					-- LEWO/PRAWO , GORA/DOL , TYL/PRZOD
					self.scene:snapCameraPosition(0,1.5,-5);
					self.scene:snapCameraLookTo(0,1,10);
					self.cameraSnapToMy = true
					--print ("SNAP CAMERA");
				else
					self.scene:snapCameraTo(nil)
					self.cameraSnapToMy = false
					--print ("UNSNAP CAMERA");
				end
				
			end
			
			-- FORWARD
			if(event.Char==87 or event.Char==119) then
				if(event.PressedDown==true) then
					if(self:getCurrentSpeedKmHour()<tonumber(self.Config.Engine.Topspeed)) then
						for i=1,xml.Body.Connectors do	
							if(self.Config['Connector'..i].Engine) then
								self:applyEngineForce(i,self.Config.Engine.Horses)
							end
						end
					else
						for i=1,xml.Body.Connectors do	
							self:applyEngineForce(i,0)
						end
					end
				else
					for i=1,xml.Body.Connectors do	
						self:applyEngineForce(i,0)
					end
				end

				return true;
			end

			if(self.sterringAngle==nil) then
				self.sterringAngle = 0;
			end

			-- LEFT
			if((event.Char==65 or event.Char==97) and event.PressedDown==true ) then
				self.sterringAngle = self.sterringAngle - tonumber(self.Config.Body.Steeringstronge);

			

				if(self.sterringAngle < -tonumber(self.Config.Body.Steeringmaxangle)) then self.sterringAngle = -tonumber(self.Config.Body.Steeringmaxangle) end

				for i=1,xml.Body.Connectors do	
					if(self.Config['Connector'..i].Steering) then
						self:setSteeringValue(i,self.sterringAngle);
					end
				end			

				return true;
			end

			-- RIGHT
			if((event.Char==68 or event.Char==100) and event.PressedDown==true ) then
				self.sterringAngle = self.sterringAngle + tonumber(self.Config.Body.Steeringstronge);



				if(self.sterringAngle>tonumber(self.Config.Body.Steeringmaxangle)) then self.sterringAngle = tonumber(self.Config.Body.Steeringmaxangle) end

				for i=1,xml.Body.Connectors do	
					if(self.Config['Connector'..i].Steering) then
						self:setSteeringValue(i,self.sterringAngle);
					end
				end			

				return true;
			end

			-- breake
			if((event.Char==83 or event.Char==115) and event.PressedDown==true ) then
				for i=1,xml.Body.Connectors do	
					if(self.Config['Connector'..i].Break) then
						print ("SET BREAK "..i);
						self:setBrake(i,self.Config.Breakes.Breakstrong);
					end
				end	
			else
				for i=1,xml.Body.Connectors do	
					if(self.Config['Connector'..i].Break) then
						self:setBrake(i,0);
					end
				end
			end

			-- handbreake
			if((event.Char==32) and event.PressedDown==true ) then
				for i=1,xml.Body.Connectors do	
					if(self.Config['Connector'..i].Handbreak) then
						print ("SET HANDBREAK "..i);
						self:setBrake(i,self.Config.Breakes.Handbreakstrong);
					end
				end	
			else
				for i=1,xml.Body.Connectors do	
					if(self.Config['Connector'..i].Handbreak) then
						self:setBrake(i,0);
					end
				end	
			end

			return false;
		    end

		if (scene~=nil) then
			scene:addObject(car);
		end

	return car;
end]]
