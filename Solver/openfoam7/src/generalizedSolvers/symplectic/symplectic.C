/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "symplectic.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace generalizedSolvers
{
    defineTypeNameAndDebug(symplectic, 0);
    addToRunTimeSelectionTable(generalizedSolver, symplectic, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::generalizedSolvers::symplectic::symplectic
(
    const dictionary& dict,
    generalizedMotion& body
)
:
    generalizedSolver(body)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::generalizedSolvers::symplectic::~symplectic()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::generalizedSolvers::symplectic::solve
(
    bool firstIter,
    const List<scalar>& fbar,
    scalar deltaT,
    scalar deltaT0
)
{
    // First simplectic step:
    //     Half-step for linear and angular velocities
    //     Update position and orientation

    vbar() = vbar0() + 0.5*deltaT0*abar0();
    ubar() = ubar0() + deltaT*vbar();

    // Update the linear acceleration and torque
    updateAcceleration(fbar);

    // Second simplectic step:
    //     Complete update of velocity

    vbar() = vbar() + 0.5*deltaT*abar();
}


// ************************************************************************* //
