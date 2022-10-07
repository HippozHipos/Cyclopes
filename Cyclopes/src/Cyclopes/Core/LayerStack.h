#pragma once

#include <vector>
#include <memory>

#include "Layer.h"
#include "Cyclopes/Event/Event.h"

#include "Cyclopes/Renderer/GraphicsContext.h"


//TODO: ADD THE ABILITY TO REMOVE LAYER. 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												SUMMARY
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Layers can be pushed 
//into layerstack, but the layerstack will not take ownership of the layers. Client is responsible
//for owninf and managing the lifetime of layers.

//For every layer that is pushed, layerstack is responsible for calling OnInit, OnUpdate, OnImGuiRender, OnEvent and OnDestroy
//functions of those layers. 
//This iteration happens in reverse order. So the last layer added to the stack gets called first.

//Functions for pushing layers make sure that overlays are only added at the back of the stack.

//OnEvent function is only called for a layer if the layer above it sets the "progagate" member of the event it
//recieves to be true. This way each layer can decide if it wants the layer bellow it to recieve events.

//OnAttach, OnUpdate and OnDetach functions are called by the application class for each layerstack.
//OnEvent function is called by the window that the layer stack belongs to.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace cyc {

	class Renderer2D;
	class LayerStack
	{
	public:
		LayerStack(Window* window);

	public:
		//client  side
		void PushLayer(Layer* layer, int index, bool overlay = false);
		void PushFrontLayer(Layer* layer, bool overlay = false);
		void PushBackLayer(Layer* layer, bool overlay = false);

	public:
		void _OnAttach(Renderer2D* r2d, GraphicsContext* gfx);
		void _OnEvent(Event& e);
		void _OnUpdate();
		void _OnDetach();
		void _OnImGuiRender();

	private:
		Cyc_Vector<Layer*> m_Layers;
		Window* window = nullptr;
		Renderer2D* renderer2D = nullptr;
		GraphicsContext* gfx = nullptr;
		int m_NOverlays = 0; //number of overlay layers
		int m_NNonOverlays = 0; //number of non-overlay layers
	};

}
