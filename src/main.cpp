/*
	Copyright 2023 Somnium Chase

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "mitake.h"

#include <iostream>

int main(int argc, char* argv[])
{
	std::vector<uint8_t> data;
	Point p {4220141, 2521342, 123152};
	MITAKE mtk;
	mtk.writePoint(data, p);

	for (auto i = 0; i < data.size(); ++i)
	{
		std::cout << data[i];
	}

	return 0;
}