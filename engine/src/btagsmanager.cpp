/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "../include/btagsmanager.h"

namespace BackGenEngine {

    BTagsManager::BTagsManager ( BLogger *logger ) : RootTag ( "_ROOT_" ), Logger ( logger ) {
    }

    BTagsManager::~BTagsManager() {
        btag_hash_t::Iterator it = Tags.begin();
        while ( it != Tags.end() ) {
            delete ( *it );
            ++it;
        }
    }

    BTag &BTagsManager::rootTag() {
        return RootTag;
    }

    bool BTagsManager::containTag ( const BoxE::Core::BAsciiString &name  ) const {
        return Tags.contains ( name );
    }

    BTag *BTagsManager::createTag ( const BoxE::Core::BAsciiString &name ) {
        if ( Tags.contains ( name ) ) {
            return 0;
        }

        BTag *new_tag = new BTag ( name );

        if ( insertTag ( new_tag ) ) {
            return new_tag;
        } else {
            delete new_tag;
            return 0;
        }
    }

    BTag *BTagsManager::getTag ( const BoxE::Core::BAsciiString &name ) {
        btag_hash_t::Iterator it = Tags.find ( name );
        if ( it != Tags.end() ) {
            return ( *it );
        } else {
            return 0;
        }
    }

    bool BTagsManager::removeTag ( const BoxE::Core::BAsciiString &name ) {
        return removeTag ( getTag ( name ) );
    }

    const BTagsManager::btag_hash_t &BTagsManager::tagsHash() const {
        return Tags;
    }

    BoxE::Core::BByteArray BTagsManager::toByteArray() {
        BoxE::Core::BByteArray str ( "tags_manager {\n"
                                     "%1"
                                     "}\n" );

        BoxE::Core::BByteArray tags_str;
        BoxE::Core::BByteArray tag_str;

        btag_hash_t::Iterator it = Tags.begin();
        while ( it != Tags.end() ) {
            tag_str = "\ttag %1\n";
            tag_str.replace ( "%1", ( *it )->getName() );

            tags_str.append ( tag_str );
            ++it;
        }

        str.replace ( "%1", tags_str );

        return str;
    }

    bool  BTagsManager::fromByteArray ( const BoxE::Core::BByteArray &byte_array ) {
        BoxE::Core::BLinkedList<BoxE::Core::BByteArray> list = byte_array.split ( ' ' );

        int block_count = 0;
        BoxE::Core::BLinkedList<BoxE::Core::BByteArray>::ConstIterator it = list.constBegin();
        while ( it != list.constEnd() ) {
            if ( ( *it ) == "tags_manager" ) {
                if ( ++it == list.constEnd() ) {
                    return false;
                }

                if ( ( *it ) == "{" ) {
                    block_count = 1;
                } else {
                    return false;
                }

                while ( block_count != 0 ) {
                    if ( ++it == list.constEnd() ) {
                        return false;
                    }

                    if ( ( *it ) == "}" ) {
                        block_count--;

                    } else if ( ( *it ) == "tag" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BoxE::Core::BByteArray name = ( *it );
                        createTag ( name );
                    }
                }
            } else {
                return false;
            }
        }
    }

    bool BTagsManager::removeTag ( BTag *tag ) {
        if ( tag == 0 ) {
            return false;
        }

        btag_hash_t::Iterator it = Tags.find ( tag->getName() );
        if ( it != Tags.end() ) {
            Tags.erase ( it );
            ( *it )->onNameChanged().disconnect ( this, &BTagsManager::onTagNameChaned );
            return true;
        } else {
            return false;
        }
    }

    bool BTagsManager::insertTag ( BTag *tag ) {
        if ( tag == 0 ) {
            return false;
        }

        if ( containTag ( tag->getName() ) ) {
            return false;
        }

        if ( Tags.insert ( tag->getName(), tag ) ) {
            tag->onNameChanged().connect ( this, &BTagsManager::onTagNameChaned );
            return true;

        } else {
            return false;
        }

    }

    void BTagsManager::onTagNameChaned ( BTag *tag, BoxE::Core::BAsciiString new_name  ) {
        btag_hash_t::Iterator it = Tags.begin();
        while ( it != Tags.end() ) {
            if ( ( *it ) == tag ) {
                Tags.erase ( it );
                Tags.insert ( new_name, tag );
                return;
            }
            ++it;
        }
    }
}
