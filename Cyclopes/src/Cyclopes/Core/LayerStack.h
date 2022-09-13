#pragma once

#include <vector>
#include <memory>

#include "Layer.h"
#include "Cyclopes/Event/Event.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												SUMMARY
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Layer stack is owned by window so there is a layer stack for every window. Layers can be pushed 
//into layerstack, but the layerstack will not take ownership of the layers. Client is responsible
//for owninf and managing the lifetime of layers.

//For every layer that is pushed, layerstack is responsible for calling OnInit, OnUpdate, OnEvent and OnDestroy
//functions of those layers. 
//This iteration happens in reverse order. So the last layer added to the stack gets called first.

//Functions for pushing layers make sure that overlays are only added at the back of the stack.

//Window that the layer stack belongs to needs to be registered to the application before the layer system
//can be used.

//OnEvent function is only called for a layer if the layer above it sets the "progagate" member of the event it
//recieves to be true. This way each layer can decide if it wants the layer bellow it to recieve events.

//OnAttach, OnUpdate and OnDetach functions are called by the application class for each layerstack.
//OnEvent function is called by the window that the layer stack belongs to.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace cyc {

	class Win32NativeWindow;
	class Application;

	class LayerStack
	{
		//These classes are friended so that the only public functions of this class are the push... functions.

		//uses OnEvent function
		friend class Win32NativeWindow;

		//uses OnAttach, OnUpdate, OnDetach functions
		friend class Application;
	public:
		LayerStack(Window* window);

	public:
		//client  side
		void PushLayer(Layer* layer, int index, bool overlay = false);
		void PushFrontLayer(Layer* layer, bool overlay = false);
		void PushBackLayer(Layer* layer, bool overlay = false);

	private:
		void AssertWindowRegistered(const Layer* layer, const Cyc_String& funcName) const;

	private:
		void OnAttach(Renderer* renderer);
		void OnEvent(Event& e);
		void OnUpdate();
		void OnDetach();
		void OnImGuiRender();

	private:
		Cyc_Vector<Layer*> m_Layers;
		Window* m_Window = nullptr;
		Renderer* renderer = nullptr;
		int m_NOverlays = 0; //number of overlay layers
		int m_NNonOverlays = 0; //number of non-overlay layers
	};

}
