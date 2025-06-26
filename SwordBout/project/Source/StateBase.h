#pragma once
class GameObject;

class StateBase {
public:
	StateBase(GameObject* base) {baseObject = base;}
	virtual ~StateBase() {}
	virtual void Resume() {} // �ĊJ
	virtual void Update() {} // �X�V
	virtual void Suspend() {} // �ꎞ��~
protected:
	GameObject* baseObject;
	template<class C>
	C* GetBase() {
		return dynamic_cast<C*>(baseObject);
	}
};