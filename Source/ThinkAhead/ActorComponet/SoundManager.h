// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THINKAHEAD_API USoundManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	USoundManager();

	float GetSoundVolume() { return SoundsVolume; }
	float GetMusicVolume() { return MusicVolume; }
	void SetSoundVolume(float NewVolume) { SoundsVolume = NewVolume; }
	void SetMusicVolume(float NewVolume) { MusicVolume = NewVolume; }

	void StopAmbientSounds();
	void StopMusic();

	void PlayAmbientSounds();
	void PlayMusic();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	private:

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* BackgroundMusic;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* NatureSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* StreamSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	float MusicVolume;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	float SoundsVolume;

	class UAudioComponent* MusicAudioComp;
	class UAudioComponent* NatureAudioComp;
	class UAudioComponent* StreamAudioComp;

		
};
