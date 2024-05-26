// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "cppEdgeOutput.h"
#include "GameFramework/Actor.h"
#include "cppEdge.generated.h"


UCLASS()
class PRJ_API AcppEdge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AcppEdge();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


USTRUCT(BlueprintType)
struct PRJ_API FoutputEdge
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int outputId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float factor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flow;
public:

};

USTRUCT(BlueprintType)
struct PRJ_API Ffedge
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* fromNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* toNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int N_in;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int N_out;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float optimal_concentration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float optimal_speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<int> input_roads;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, FoutputEdge> output_roads;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float concentration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float leave = 0.0;

	float leaveSpeed = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flow_1 = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flow_sum = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSimulatedLocal = false;

public:

};