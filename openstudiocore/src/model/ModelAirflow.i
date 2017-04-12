#ifndef MODEL_AIRFLOW_I
#define MODEL_AIRFLOW_I

#ifdef SWIGPYTHON
  %module openstudiomodelairflow
#endif


%include <model/Model_Common_Include.i>
%import <model/ModelCore.i>
%import <model/ModelSimulation.i>
%import <model/ModelResources.i>
%import <model/ModelGeometry.i>

//%{
//  #include <model/HVACTemplates.hpp>
//%}

#if defined SWIGCSHARP

  #undef _csharp_module_name
  #define _csharp_module_name OpenStudioModelAirflow
  
#endif

// Base classes
MODELOBJECT_TEMPLATES(AirflowNetworkComponent);
MODELOBJECT_TEMPLATES(AirflowNetworkNode);

SWIG_MODELOBJECT(AirflowNetworkComponent, 1);
SWIG_MODELOBJECT(AirflowNetworkNode, 1);

// The rest
MODELOBJECT_TEMPLATES(AirflowNetworkConstantPressureDrop);
MODELOBJECT_TEMPLATES(AirflowNetworkCrack);
MODELOBJECT_TEMPLATES(AirflowNetworkDetailedOpening);
MODELOBJECT_TEMPLATES(AirflowNetworkDuct);
MODELOBJECT_TEMPLATES(AirflowNetworkEffectiveLeakageArea);
MODELOBJECT_TEMPLATES(AirflowNetworkEquivalentDuct);
MODELOBJECT_TEMPLATES(AirflowNetworkExternalNode);
MODELOBJECT_TEMPLATES(AirflowNetworkFan);
MODELOBJECT_TEMPLATES(AirflowNetworkHorizontalOpening);
MODELOBJECT_TEMPLATES(AirflowNetworkLeakageRatio);
MODELOBJECT_TEMPLATES(AirflowNetworkLinkage);
MODELOBJECT_TEMPLATES(AirflowNetworkReferenceCrackConditions);
MODELOBJECT_TEMPLATES(AirflowNetworkSimpleOpening);
UNIQUEMODELOBJECT_TEMPLATES(AirflowNetworkSimulationControl);
MODELOBJECT_TEMPLATES(AirflowNetworkSurface);
MODELOBJECT_TEMPLATES(AirflowNetworkZoneExhaustFan);

SWIG_MODELOBJECT(AirflowNetworkConstantPressureDrop, 1);
SWIG_MODELOBJECT(AirflowNetworkCrack, 1);
SWIG_MODELOBJECT(AirflowNetworkDetailedOpening, 1);
SWIG_MODELOBJECT(AirflowNetworkDuct, 1);
SWIG_MODELOBJECT(AirflowNetworkEffectiveLeakageArea, 1);
SWIG_MODELOBJECT(AirflowNetworkEquivalentDuct, 1);
SWIG_MODELOBJECT(AirflowNetworkExternalNode, 1);
SWIG_MODELOBJECT(AirflowNetworkFan, 1);
SWIG_MODELOBJECT(AirflowNetworkHorizontalOpening, 1);
SWIG_MODELOBJECT(AirflowNetworkLeakageRatio, 1);
SWIG_MODELOBJECT(AirflowNetworkLinkage, 1);
SWIG_MODELOBJECT(AirflowNetworkReferenceCrackConditions, 1);
SWIG_MODELOBJECT(AirflowNetworkSimpleOpening, 1);
SWIG_UNIQUEMODELOBJECT(AirflowNetworkSimulationControl);
SWIG_MODELOBJECT(AirflowNetworkSurface, 1);
SWIG_MODELOBJECT(AirflowNetworkZoneExhaustFan, 1);

//#if defined(SWIGCSHARP) || defined(SWIGJAVA)
//  %inline {
//    namespace openstudio {
//      namespace model {
//        std::vector<openstudio::model::ThermalZone> getThermalZones(const openstudio::model::Building& building){
//          return building.thermalZones();
//        }
//        boost::optional<openstudio::model::ThermalZone> getThermalZone(const openstudio::model::Space& space){
//          return space.thermalZone();
//        }
//        bool setThermalZone(openstudio::model::Space space, openstudio::model::ThermalZone thermalZone){
//          return space.setThermalZone(thermalZone);
//        }
//      }
//    }
//  }
//#endif

//#if defined(SWIGCSHARP)
//  //%pragma(csharp) imclassimports=%{
//  %pragma(csharp) moduleimports=%{
//  
//    using System;
//    using System.Runtime.InteropServices;
//        
//    public partial class Building : ParentObject {
//      public ThermalZoneVector thermalZones()
//      {
//        return OpenStudio.OpenStudioModelHVAC.getThermalZones(this);
//      }
//    }  
    
//    public partial class Space : PlanarSurfaceGroup {
//      public OptionalThermalZone thermalZone()
//      {
//        return OpenStudio.OpenStudioModelHVAC.getThermalZone(this);
//      }
//      public bool setThermalZone(OpenStudio.ThermalZone thermalZone)
//      {
//        return OpenStudio.OpenStudioModelHVAC.setThermalZone(this, thermalZone);
//      }
//    }  
//  %}
//#endif

//%include <model/HVACTemplates.hpp>

#endif 