//**************************************************************************/
// Copyright (c) 1998-2008 Autodesk, Inc.
// All rights reserved.
// 
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.
//**************************************************************************/
// DESCRIPTION: PerformanceTools (namespace)
//				Tools to track performance counters and thread settings
// AUTHOR:	Peter Watje	-  April 22, 2008
//			
//***************************************************************************/
#pragma once

#include "MaxHeap.h"
#include <WTypes.h>

namespace MaxSDK 
{
	namespace PerformanceTools 
	{

		//! \brief This class lets control the amount of threading in different parts of Max */
		class ThreadTools : public MaxHeapOperators
		{
		public:
			enum ThreadType { kMeshThreading = 0, //the internal threading to mesh this mainly building normals, some clip operations, and vec normalization
				   kDeformationThreading,		  //this controls the threading of the simple deformation class that is used by modifiers like bend, skin, skinwrap etc 
				   kHWMeshCreationThreading, //this the numbers of threads used to create the DirectX hardware meshes
				   kEndThreading // do not use this just signifies the end of the enumeration.  Insert any new enumeration above this one
				 } ;


			//! \brief This method lets you set the number of threads on various parts of Max
			/*!	This method lets you set the maximum number of threads on various parts of Max. It also lets
				you set the minimum number of elements for each thread to prevent excessiving threading. It does not
				prevent you from oversubscribing threads.
			\param[in] threadType this is which part of Max you want to set the multi-thread level
			\param[in] maxNumThreads this is the maximum number of threads to use for this operation.  This is not limited so you can over subscribe and have more threads than CPUs.
			\param[in] minElementsPerThread this is used to restrict the number of threads.  It controls the number of threads to use limited by maxNumThreads.  The number of threads used
						equal to numberElements/minElementsPerThread.  So for instance the KMeshThreads in the elements
						are the faces/vertices.	This is here to prevent too few elements per thread.
						If set to 0 or less this value will be ignored and the numThreads will be used.
			*/
			UtilExport static void SetNumberOfThreads(ThreadType threadType, unsigned int maxNumThreads, unsigned int minElementsPerThread);
			//! \brief This method returns the maximum number of threads on various parts used by Max
			/*!	This method returns the maximum number of threads on various parts of used by Max.
			\param[in] threadType this is which part of Max you want to set the multi-thread level
			*/
			UtilExport static unsigned int GetNumberOfThreads(ThreadType threadType);
			//! \brief This method returns the minimum number elements in each threads on various parts used by Max
			/*!	This method returns the minimum number elements in each threads on various parts used by Max
			\param[in] threadType this is which part of Max you want to set the multi-thread level
			*/
			UtilExport static unsigned int GetMinNumberElements(ThreadType threadType);

			//! \brief This method returns the actual number of threads to be used for a particular task depending on the number of elements
			/*!	This method returns the actual number of threads to be used for a particular task depending on the number of elements
			\param[in] threadType this is which part of Max you want to get the multi-thread level
			\param[in] numberElements is the number of elements in the loop to thread
			*/
			UtilExport unsigned int GetNumberOfThreads(ThreadType threadType, unsigned int numberElements);


			//! \brief This method returns the optimal grainsize to be used with Intel's TBB parallel_for and similar functions
			/*! It will cap the amount of work according to the number of threads available - 1, or the setting in your preference ini file.
			 * If the MaxThreads setting is higher than number of threads available -1, we cap the thread count.
			\param[in] iterationCount this is the number of elements you will iterate over
			*/
			UtilExport static size_t TbbGrainsize(size_t iterationCount);

			//! \brief This method sets the maximum number of threads for Tbb.
			/*! This value should be set in the currentdefaults.ini preference file.
			\param[in] numThreads The number of threads to use, -1 for max available threads.
			*/
			UtilExport static void SetTbbMaxThreads(int numThreads);

			//! \brief This method return the maximum number of threads for Tbb.
			/*! It returns the appropriate value, not the value set in the preferences.
			\return numThreads The number of threads tbb will use, between 1 and max threads - 1.
			*/
			UtilExport static size_t GetTbbMaxThreads();
		};



		//! \brief Just a helper class to record how long a task takes.  Just call this at the start and EndTimer at the end will return the amount of time that has passed in milliseconds
		class Timer : public MaxHeapOperators
		{
		public:
	
			/*! \brief This methods let you start a local timer.  Use these 2 methods if you are just timing a local block once*/
			UtilExport void StartTimer();
			/*! \brief This methods returns the amount of time in milliseconds that has passed since StartTimer.*/
			UtilExport double EndTimer();

			/*! \brief These are global timers that can be started and stopped in different scopes.  There are 1000 ids and the first 100 are reserverd for internal */
			/*! \brief This starts a timer matching the ID*/
			UtilExport static void StartTimerGlobal(unsigned int id);
			/*! \brief This ends a timer matching the ID and returns the accumlated time passed in MS*/
			UtilExport static double EndTimerGlobal(unsigned int id);
			/*! \brief This clears a timer matching the ID */
			UtilExport static void ClearTimerGlobal(unsigned int id);
			/*! \brief This returns the amount of  time passed for the matching ID */
			UtilExport static double GetTimerGlobal(unsigned int id);


		private:
			LARGE_INTEGER mStartTime, mEndTime;

		};

		//! \brief Just a helper class to record how long a block of code.  it starts a timer when constructed and stops when destructed.  Useful for code block with lots of breaks and/or returns. 
		class TimeBlock : public MaxHeapOperators
		{
		public:
			/*! \brief Starts a timer tied to the id example
				{
					TimeBlock timeBlock(15);
					<...> code to time
				}
				double result - Timer::GetTimerGlobal(15);

			*/
			UtilExport TimeBlock(unsigned int id);
			UtilExport ~TimeBlock();

		protected:
			unsigned int mID = 0;
		};

	}
}

