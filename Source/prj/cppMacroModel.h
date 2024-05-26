// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "cppEdge.h"
#include "GameFramework/Actor.h"
#include <unordered_map>
#include "cppMacroModel.generated.h"

UCLASS()
class PRJ_API AcppMacroModel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AcppMacroModel();

	//std::unordered_map<int32, Ffedge> models;
	UPROPERTY()
	TMap<int32, Ffedge> edges;

	UFUNCTION(BlueprintCallable)
	void AddEdge(UPARAM(ref) Ffedge& edge) {
		auto id = edge.id;

		edges.Add(id,edge);
	};

	UFUNCTION(BlueprintCallable)
	Ffedge GetEdge(int32 edge) {
		return edges.FindRef(edge);
	};

	UFUNCTION(BlueprintCallable)
	TMap<int32, Ffedge> GetEdges() {
		return edges;
	};

	UFUNCTION(BlueprintCallable)
	void SetLocalSimulated(int id, bool value) {
		edges[id].isSimulatedLocal = value;
	};

	UFUNCTION(BlueprintCallable)
	void SetZeroConcetration(int id) {
		edges[id].concentration = 0;
	};

	UFUNCTION(BlueprintCallable)
	void IncreaseConcentration(int id) {
		edges[id].concentration += 1;
	};

	UFUNCTION(BlueprintCallable)
	void DecreaseConcentration(int id) {
		edges[id].concentration -= 1;
	};

	UFUNCTION(BlueprintCallable)
	Ffedge GetNextRandomNode(int id) {
		auto output = edges[id].output_roads;
		auto num = output.Num();
		TArray<int> keys;
		output.GetKeys(keys);
			
		
		auto nextIndex = FMath::RandRange(0, num - 1);
		auto next = output[keys[nextIndex]].outputId;
		return edges[next];
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TickModel();

	void StepOne();
	void StepTwo();
	void StepThree();

	float rememberedTime = 0;
	float Delta = 1;
};
