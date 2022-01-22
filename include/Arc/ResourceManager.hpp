#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																											  //
//  Arc - SFML Vertex Array Utilities																		  //
//  Copyright (C) 2021 Kan																					  //
//    																										  //
//  This software is provided 'as-is', without any express or implied warranty.								  //
//  In no event will the authors be held liable for any damages arising from the use of this software.		  //
//																											  //
//  Permission is granted to anyone to use this software for any purpose, including commercial applications,  //
//  and to alter it and redistribute it freely, subject to the following restrictions:						  //
//																											  //
//		1.  The origin of this software must not be misrepresented;											  //
//			you must not claim that you wrote the original software.										  //
//			If you use this software in a product, an acknowledgment										  //
//			in the product documentation would be appreciated but											  //
//			is not required.																				  //
//																											  //
//		2.  Altered source versions must be plainly marked as such,											  //
//			and must not be misrepresented as being the original software.									  //
//																											  //
//		3.  This notice may not be removed or altered from any source distribution.							  //
//																											  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

	------------------------------------------------------------
			CLASS MEMBER FUNCTIONS
	------------------------------------------------------------
	-	AddFile()
	-	RemoveFile()
	-	GetFile()
	-	ClearFiles()
	-	LoadResource()
	-	RemoveResource()
	-	GetResource()
	-	ClearResources()
	-	Clear()

	------------------------------------------------------------
			BASIC USAGE
	------------------------------------------------------------

	int main() {

		Arc::ResourceManager<std::string, sf::Texture> textures;

		// first you add all the texture files that you may need
		textures.AddFile("tex_1", "path_to/my/texture.png");
		textures.AddFile("tex_2", "path_to/my/text.bmp");
		textures.AddFile("tex_3", "filepath.png");

		// second you load them
		textures.LoadResource("tex_1");
		textures.LoadResource("tex_2");

		// now you can use them
		sf::Sprite my_sprite;
		my_sprite.setTexture(texture.GetResource("tex_2"));

		// you can load and use them at the same time so long as the file is already in the container
		sf::Sprite second_sprite;
		second_sprite.setTexture(*LoadResource("tex_3"));

	}

*/

#include <SFML/Audio/Music.hpp>
#include <SFML/System/String.hpp>
#include <unordered_map>

namespace Arc {

	template <class I, class R>
	class ResourceManager {
	public:

		ResourceManager() = default;

		bool AddFile(const I& id, const sf::String& file) {
			return m_files.try_emplace(id, file).second;
		}

		void RemoveFile(const I& id) {
			m_files.erase(id);
		}

		const sf::String& GetFile(const I& id) const {
			return m_files.at(id);
		}

		void ClearFiles() {
			m_files.clear();
		}

		template <typename ...A>
		R* LoadResource(const I& id, A&& ...args) {
			auto itr_res = m_resources.find(id);
			if (itr_res != m_resources.end()) { return &itr_res->second; } // the resource already exists
			auto itr_file = m_files.find(id);
			if (itr_file == m_files.end()) { return nullptr; } // file not found
			R new_resource;
			if constexpr (std::is_same_v<R, sf::Music>) {
				if (!new_resource.openFromFile(itr_file->second)) { return nullptr; }
			}
			else {
				if (!new_resource.loadFromFile(itr_file->second, std::forward<A>(args)...)) { return nullptr; }
			}
			return m_resources.try_emplace(id, std::move(new_resource)).second ? &m_resources.at(id) : nullptr;
		}

		void RemoveResource(const I& id) {
			m_resources.erase(id);
		}

		R& GetResource(const I& id) {
			return m_resources.at(id);
		}

		void ClearResources() {
			m_resources.clear();
		}

		void Clear() {
			ClearFiles();
			ClearResources();
		}

	private:
		std::unordered_map<I, sf::String> m_files;
		std::unordered_map<I, R> m_resources;
	};

}
