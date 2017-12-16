#include"AbuPrefab.h"
#include"../Define.h"

USING_NAMESPACE_ALA;

void AbuPrefab::doInstantiate(ala::GameObject* object) const {
	// components
	const auto spriteRenderer = new SpriteRenderer(object, "abu.png");
	const auto animator = new Animator(object, "fan", "abu.anm");
}