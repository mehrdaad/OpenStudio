/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2016, Alliance for Sustainable Energy, LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *  disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *  following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
 *  products derived from this software without specific prior written permission from the respective party.
 *
 *  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
 *  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
 *  specific prior written permission from Alliance for Sustainable Energy, LLC.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#include "../ForwardTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/GasEquipment.hpp"
#include "../../model/GasEquipment_Impl.hpp"
#include "../../model/GasEquipmentDefinition.hpp"
#include "../../model/GasEquipmentDefinition_Impl.hpp"
#include "../../model/Space.hpp"
#include "../../model/Space_Impl.hpp"
#include "../../model/SpaceType.hpp"
#include "../../model/SpaceType_Impl.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/ThermalZone_Impl.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/LifeCycleCost.hpp"

#include <utilities/idd/GasEquipment_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateGasEquipment( GasEquipment& modelObject )
{
  IdfObject idfObject(openstudio::IddObjectType::GasEquipment);
  m_idfObjects.push_back(idfObject);

  for (LifeCycleCost lifeCycleCost : modelObject.lifeCycleCosts()){
    translateAndMapModelObject(lifeCycleCost);
  }

  GasEquipmentDefinition definition = modelObject.gasEquipmentDefinition();

  idfObject.setString(GasEquipmentFields::Name, modelObject.name().get());

  boost::optional<Space> space = modelObject.space();
  boost::optional<SpaceType> spaceType = modelObject.spaceType();
  if (space){
    boost::optional<ThermalZone> thermalZone = space->thermalZone();
    if (thermalZone){
      idfObject.setString(GasEquipmentFields::ZoneorZoneListName, thermalZone->name().get());
    }
  }else if(spaceType){
    idfObject.setString(GasEquipmentFields::ZoneorZoneListName, spaceType->name().get());
  }

  boost::optional<Schedule> schedule = modelObject.schedule();
  if (schedule){
    idfObject.setString(GasEquipmentFields::ScheduleName, schedule->name().get());
  }

  idfObject.setString(GasEquipmentFields::DesignLevelCalculationMethod, definition.designLevelCalculationMethod());

  double multiplier = modelObject.multiplier();

  OptionalDouble d = definition.designLevel();
  if (d){
    idfObject.setDouble(GasEquipmentFields::DesignLevel, (*d)*multiplier);
  }

  d = definition.wattsperSpaceFloorArea();
  if (d){
    idfObject.setDouble(GasEquipmentFields::PowerperZoneFloorArea, (*d)*multiplier);
  }

  d = definition.wattsperPerson();
  if (d){
    idfObject.setDouble(GasEquipmentFields::PowerperPerson, (*d)*multiplier);
  }

  if (!definition.isFractionLatentDefaulted()){
    idfObject.setDouble(GasEquipmentFields::FractionLatent, definition.fractionLatent());
  }

  if (!definition.isFractionRadiantDefaulted()){
    idfObject.setDouble(GasEquipmentFields::FractionRadiant, definition.fractionRadiant());
  }

  if (!definition.isFractionLostDefaulted()){
    idfObject.setDouble(GasEquipmentFields::FractionLost, definition.fractionLost());
  }

  if (!definition.isCarbonDioxideGenerationRateDefaulted()){
    idfObject.setDouble(GasEquipmentFields::CarbonDioxideGenerationRate, definition.carbonDioxideGenerationRate());
  }

  if (!modelObject.isEndUseSubcategoryDefaulted()){
    idfObject.setString(GasEquipmentFields::EndUseSubcategory, modelObject.endUseSubcategory());
  }

  return idfObject;
}

} // energyplus

} // openstudio

