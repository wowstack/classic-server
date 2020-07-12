/**
 * Copyright (C) 2005-2014  MaNGOS project  <http://getmangos.com>
 * Copyright (C) 2013-2019  CMaNGOS project <http://cmangos.net>
 * Copyright (C) 2014-2019  WowStack        <https://wowstack.io/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MANGOS_GRIDLOADER_H
#define MANGOS_GRIDLOADER_H

/**
  @class GridLoader
  The GridLoader is working in conjuction with the Grid and responsible
  for loading and unloading object-types (one or more) when objects
  enters a grid.  Unloading is scheduled and might be canceled if
  an interested object re-enters.  GridLoader does not do the actuall
  loading and unloading but implements as a template pattern that
  delicate its loading and unloading for the actualy loader and unloader.
  GridLoader manages the grid (both local and remote).
 */

#include "game_system/Grid.h"
#include "game_system/TypeContainerVisitor.h"
#include "platform/Define.h"

template <class ACTIVE_OBJECT, class WORLD_OBJECT_TYPES, class GRID_OBJECT_TYPES>
class GridLoader
{
  public:
    /** Loads the grid
     */
    template <class LOADER>
    void Load(Grid<ACTIVE_OBJECT, WORLD_OBJECT_TYPES, GRID_OBJECT_TYPES> &grid, LOADER &loader)
    {
        loader.Load(grid);
    }

    /** Stop the grid
     */
    template <class STOPER>
    void Stop(Grid<ACTIVE_OBJECT, WORLD_OBJECT_TYPES, GRID_OBJECT_TYPES> &grid, STOPER &stoper)
    {
        stoper.Stop(grid);
    }

    /** Unloads the grid
     */
    template <class UNLOADER>
    void Unload(Grid<ACTIVE_OBJECT, WORLD_OBJECT_TYPES, GRID_OBJECT_TYPES> &grid, UNLOADER &unloader)
    {
        unloader.Unload(grid);
    }
};

#endif
