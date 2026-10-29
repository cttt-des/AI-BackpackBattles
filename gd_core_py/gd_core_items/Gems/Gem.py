# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gem(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Gems/Gem.gd"

	GemMode = EnumDict("GemMode", {"Weapon": 0, "Armor": 1, "Inventory": 2, "Inactive": 3})



	def _init_fields(self):
		super()._init_fields()
		self.hoveredSocket = None
		self.socket = None
		self.movebackSocket = None
		self.dropTween = None
		self.gemPower = 1.0
		self.dropPosition = None
		self.dropRotation = None
		self.quantizedRotation = None
		self.socketDetectionArea = None
		self.gemAnimation = None


	def isGem(self):
		return True


	def isOwnable(self):
		if self.socket != None:
			return self.socket.getItem().isOwnable()
		else:
			return super().isOwnable()


	def isOwnedByOpponent(self):
		if self.socket != None:
			return self.socket.getItem().isOwnedByOpponent()
		else:
			return super().isOwnedByOpponent()


	def getEffectiveOwnerType(self):
		if self.socket != None:
			return self.socket.getItem().getEffectiveOwnerType()
		else:
			return super().getEffectiveOwnerType()


	def getInventory(self):
		if self.socket != None:
			return self.socket.getItem().getInventory()
		else:
			return super().getInventory()


	def getItem(self):
		if self.socket != None:
			return self.socket.getItem()
		else:
			return None


	def isPlaced(self):
		if self.socket != None:
			return self.socket.getItem().isPlaced()
		else:
			return self.placed


	def isInInventory(self):
		if self.socket != None:
			return self.socket.getItem().isInInventory()
		else:
			return super().isInInventory()


	def getGemMode(self):
		if self.socket != None:
			if self.getItem().isWeapon():
				return self.GemMode.Weapon
			else:
				return self.GemMode.Armor
		else:
			if self.placed:
				return self.GemMode.Inventory
			else:
				return self.GemMode.Inactive


	def getGemPower(self):
		return max(0.0, self.gemPower)


	def changeGemPower(self, amount):
		self.gemPower += amount


	def getHoverPriority(self):
		if self.dragged:
			return self.DRAG_PRIORITY
		else:
			return 1


	def character(self):
		if self.getGemMode() == self.GemMode.Inactive:
			return self.ctx.player
		elif self.getGemMode() == self.GemMode.Inventory:
			return super().character()
		else:
			return self.getItem().character()


	def _process(self, _delta):
		pass

	def previewCellCollision(self):
		if ( not self.hoveredSocket and 
			( not self.movebackSocket or self.ctx.frame_counter > self.pickupFrame + 1)):
			super().previewCellCollision()


	def gainFocus(self):
		super().gainFocus()

	def loseFocus(self):
		super().loseFocus()

	def prepareLerpToSocket(self):
		pass

	def drop(self):
		return 0

	def lerpToSocket(self, interpolationPoint):
		pass

	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)


		if self.socket != None:
			self.killDropTween()
			self.movebackSocket = self.socket
			self.hoveredSocket = self.socket
			if self.socket.getItem().ownerType == _R.C("CoreConst").Owner.PlayerStorageBox:
				self.setFaceDirection(_R.C("CoreConst").FaceDirection.UP)
			else:
				self.faceDirection = self.getGlobalFaceDirection()

			self.socket.onPickupGem()


	def addToSocket(self, _socket):
		pass

	def unsocket(self):
		self.killDropTween()
		s = self.socket
		self.socket.onPickupGem()
		s.hideSocket()


	def removeFromSocket(self):
		pass

	def killDropTween(self):
		pass

	def returnToSocket(self, movebackDur=0.1):
		pass

	def hasCooldown(self):
		gemMode = self.getGemMode()
		return ((gemMode == self.GemMode.Inventory or 
					gemMode == self.GemMode.Inactive) and 
					super().hasCooldown())


	def miniActivate(self):
		super().miniActivate()
		self.playActivationAnimation_Scale(1.5)


	def prepareInventory(self):
		pass


	def prepareWeapon(self):
		pass


	def prepareArmor(self):
		pass


	def onPrepare(self):

		if self.getGemMode() == self.GemMode.Inventory:
				self.prepareInventory()
		elif self.getGemMode() == self.GemMode.Weapon:
				self.prepareWeapon()
		elif self.getGemMode() == self.GemMode.Armor:
				self.prepareArmor()


	def combatStartInventory(self):
		pass


	def combatStartWeapon(self):
		pass


	def combatStartArmor(self):
		pass


	def combatStart(self):
		super().combatStart()
		self.iterationCooldown = self.adjustCooldown()
		self.triggerTime = self.iterationCooldown

		if self.getGemMode() == self.GemMode.Inventory:
				self.combatStartInventory()
		elif self.getGemMode() == self.GemMode.Weapon:
				self.combatStartWeapon()
		elif self.getGemMode() == self.GemMode.Armor:
				self.combatStartArmor()


	def combatEndInventory(self):
		pass


	def combatEndWeapon(self):
		pass


	def combatEndArmor(self):
		pass


	def combatEnd(self):
		super().combatEnd()
		if self.getGemMode() == self.GemMode.Inventory:
				self.combatEndInventory()
		elif self.getGemMode() == self.GemMode.Weapon:
				self.combatEndWeapon()
		elif self.getGemMode() == self.GemMode.Armor:
				self.combatEndArmor()


	def shopEntered(self, craft):
		super().shopEntered(craft)
		self.gemPower = 1.0


	def getBaseDescription(self, wrapInColor=True):
		return super().getDescription(wrapInColor)


	def getDescription(self, wrapInColor=True):
		descr = self.getBaseDescription(wrapInColor)
		colors = [self.ctx.util.inactiveColor, self.ctx.util.inactiveColor, self.ctx.util.inactiveColor]
		gemMode = self.getGemMode()
		if gemMode != self.GemMode.Inactive:
			colors[gemMode] = self.ctx.util.modifiedColor
		return self.getModeDescription(descr, colors, True, wrapInColor)


	def onHotSwapHoverWithGem(self):
		pass


	def onHotSwapHoverWithGemEnd(self):
		pass


	def createGemParticles(self):
		pass


	def canPreviewFusions(self):
		if self.socket:
			return self.socket.getItem().canPreviewFusions()
		else:
			return super().canPreviewFusions()


	def canModifyChance(self):
		return False


	def getNeighborItemsAndGems(self):
		if self.socket:
			if self.getItem().ownerType == _R.C("CoreConst").Owner.PlayerStorageBox:
				return []



			neighbors = [self.getItem()]
			neighbors.extend(self.getItem().getNeighborItemsAndGems())
			_erase(neighbors, self)
			return neighbors
		else:
			return super().getNeighborItemsAndGems()


	def canCombine(self):
		if self.socket:
			return True
		else:
			return super().canCombine()


	def shift(self, direction):
		if not self.socket:
			super().shift(direction)


	def isMovingBack(self):
		return False

	def addToStorageBox(self, addImpulse=True, tweenBouncyness=True, checkCollisions=True, targetPos=None, speed=1.0, secondCheck=False):
		if self.socket:
			s = self.socket
			super().addToStorageBox(addImpulse, tweenBouncyness, 
				checkCollisions, targetPos, speed, secondCheck)
			s.onPickupGem()
			s.hideSocket()
		else:
			super().addToStorageBox(addImpulse, tweenBouncyness, 
				checkCollisions, targetPos, speed, secondCheck)


	def discard(self, discardGems=True):
		super().discard(discardGems)
		if self.socket != None:
			self.socket.gem = None
			self.socket.hideSocket()
			self.socket = None
			self.movebackSocket = None

	def _readyInit(self):
		super()._readyInit()
		if self.descriptor.gateItem == self.ctx.item_book.getDescriptor("Box of Riches"):
			if (not self.specificDragParticles):
				pass



_R.reg("res://gd_core_items/Gems/Gem.gd", Gem)
_R.reg("Gem", Gem)
_R.reg("Gem", Gem)
