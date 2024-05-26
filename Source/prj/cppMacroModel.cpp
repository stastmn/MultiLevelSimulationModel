// Fill out your copyright notice in the Description page of Project Settings.

#include "cppMacroModel.h"
#include <algorithm>

// Sets default values
AcppMacroModel::AcppMacroModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AcppMacroModel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AcppMacroModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	rememberedTime += DeltaTime;

	if (rememberedTime >= Delta) {
		rememberedTime = 0;
		TickModel();
	}
}



void AcppMacroModel::TickModel() {

	StepOne();
	StepTwo();
	StepThree();
	
	int a = 2;
	int b = a;
}


void AcppMacroModel::StepOne() {

	for (auto& it : edges) {
		auto& id = it.Key;
		auto& edge = it.Value;

		double optimal_flow = edge.optimal_speed * edge.optimal_concentration;

		if (edge.concentration > edge.optimal_concentration)
		{

			edge.leave = optimal_flow;
			edge.leaveSpeed = edge.optimal_speed;
			//model.flow_1 =  optimal_flow - (optimal_flow * ((model.concentration - model.optimal_concentration) / model.optimal_concentration));
			edge.flow_1 = 2 * optimal_flow - edge.optimal_speed * edge.concentration;
			if (edge.flow_1 < 0) {
				edge.flow_1 = 0;
			}

		}
		else {												 //HERE
			//model.leave = optimal_flow * model.concentration < 0 ? 0 : model.concentration / model.optimal_concentration;
			edge.leave = edge.optimal_speed * edge.concentration;
			edge.leaveSpeed = edge.optimal_speed;
			edge.flow_1 = optimal_flow;

		}

	}
}


void AcppMacroModel::StepTwo() {

	for (auto& it : edges) {
		auto& id = it.Key;
		auto& edge = it.Value;

		double total_in_flow = 0;
		//TMap<int, double> roads;
		std::unordered_map<int, double> roads;
		for (auto& in_id : edge.input_roads) {
			double in_flow = edges[in_id].leave * edges[in_id].output_roads[id].factor;
			total_in_flow += in_flow;
			roads[in_id] = in_flow;

		}

		if (total_in_flow > edge.flow_1) {
			edge.flow_sum = edge.flow_1;

			for (auto& itt : roads) {
				auto in_id = itt.first;
				auto flow = itt.second;

				edges[in_id].output_roads[id].flow = edge.flow_1 * flow / total_in_flow;

			}

		}
		else {
			edge.flow_sum = total_in_flow;
			for (auto& itt : roads) {
				auto in_id = itt.first;
				auto flow = itt.second;

				edges[in_id].output_roads[id].flow = flow;

			}

		}

	}
}



void AcppMacroModel::StepThree() {

	for (auto& it : edges) {
		auto& id = it.Key;
		auto& edge = it.Value;

		float enter = 0;
		for (auto itt : edge.output_roads) {
			auto& in_id = itt.Key;
			auto& output_road = itt.Value;

			enter += output_road.flow;

		}
		
		edge.flow = FMath::Min(edge.leave, enter);
		double delta = Delta / edge.size * (edge.flow_sum - edge.flow);

		float inputConc = 0.0;

		for (auto itt : edge.input_roads) {
			inputConc += edges[itt].output_roads[id].flow / edges[itt].leaveSpeed;
		}

		float outputConc = 0.0;

		for (auto itt : edge.output_roads) {
			outputConc += itt.Value.flow / edge.leaveSpeed;
		}

		auto input = edge.isSimulatedLocal ? 0 : edge.N_in;
		auto output = edge.isSimulatedLocal ? 0 : edge.N_out;

		auto newConc = edge.concentration + inputConc - outputConc + input * Delta - output * Delta;

		if (newConc >= 0) {
			edge.concentration = newConc;
		}
		else {
			edge.concentration = 0;
		}


	}
}

