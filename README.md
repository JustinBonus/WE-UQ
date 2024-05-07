#

<div style="display: flex; justify-content: center;">
  <a href="https://github.com/NHERI-SimCenter/WE-UQ/#gh-light-mode-only"><img width=256px src="./icons/NHERI-WEUQ-Icon_LightMode_BorderRight.svg#gh-light-mode-only" align="left" /></a>
  <a href="https://github.com/NHERI-SimCenter/WE-UQ/#gh-dark-mode-only"><img width=256px src="./icons/NHERI-WEUQ-Icon_DarkMode_BorderRight.svg#gh-dark-mode-only" align="left" /></a>
  <span style="display:inline-block; width: 25px;"></span>
  <div>
    <p>
      <h3 class="subtitle"><b>WE-UQ - Desktop App</b></h3>
      <h3>Wind Engineering with Uncertainty Quantification</h3>
      <h5><i>Frank McKenna , Abiy F. Melaku, Fei Ding, Jiawei Wan, Peter Mackenzie-Helnwein, Sang-ri Yi, Michael Gardner, Wael Elhaddad</i></h5>
      <h5>NHERI SimCenter, 2017-2025</h5>
      <br>
    </p>
  </div>
</div>

---

[![Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/WE-UQ?color=blue&label=Latest%20Release)](https://github.com/NHERI-SimCenter/WE-UQ/releases/latest)   <span style="display:inline-block; width: 20px;"></span> [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.3274227.svg)](https://doi.org/10.5281/zenodo.3274227)   <span style="display:inline-block; width: 20px;"></span> [![Build status](https://ci.appveyor.com/api/projects/status/k1cfrfmjsq14akso?svg=true)](https://ci.appveyor.com/project/fmckenna/we-uq)  <span style="display:inline-block; width: 20px;"></span> [![License](https://img.shields.io/badge/License-BSD%202--Clause-blue)](https://raw.githubusercontent.com/NHERI-SimCenter/WE-UQ/master/LICENSE)  <span style="display:inline-block; width: 20px;"></span> [![GitHub](https://img.shields.io/badge/NHERI--SimCenter-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter)  <span style="display:inline-block; width: 20px;"></span>  [![LinkedIn Follow](https://img.shields.io/badge/nheri--simcenter-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/company/nheri-simcenter) <span style="display:inline-block; width: 20px;"></span>  [![YouTube Subscribe](https://img.shields.io/badge/DesignSafe-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)](https://www.youtube.com/@DesignSafe) <span style="display:inline-block; width: 20px;"></span>  

---

<div style="display: flex; justify-content: center;">
    <img src="./icons/NHERI-WEUQ-GUI_EVT_IsolatedBuilding.svg" alt="WE-UQ GUI - EVT - CFD on Isolated Building - Willis Tower" width="45.5%"/>
    <img src="./icons/NHERI-WEUQ_WindVelocityOverGableRoofedResidence.gif" alt="WE-UQ 3D CFD - Velocity of Wind Flowing Over a Gable-Roofed Residence" width="50%" />
</div>

---

# Why Use WE-UQ?

The ``WE-UQ`` desktop application is a user-facing portal for cutting-edge engineering workflows targeting extreme wind demands on structures. It is a free, open-source, graphical software for simulating a structures's response with uncertainty quantification (UQ) during extreme wind natural hazard loading. The application's interchangeable workflow allows you to swap between popular uncertainty quantification methods (e.g. Sensitivity, Reliability, Surrogates) to upgrade your previously deterministic models. Modular design lets you drop-in your own building models (SIM), event types (EVT), nonlinear structural analysis (FEM), engineering demand parameters (EDP), and more.


## Capabilities

- Drop-in uncertainty quantification (UQ) methods like forward propagation, sensitivity, and reliability analysis onto previously deterministic computational fluid dynamics (CFD) models using ``SimCenter UQ`` and/or ``Dakota`` backends
- Model experiments from validated wind flume digital twins
- Synoptic and non-synoptic wind events supported
- Generate stochastic wind loads by taking surrounding exposure conditions, turbulence characteristics, and wind speed as inputs
- Obtain wind force-time histories from existing aerodynamics databases
- Generate integrated loads and point pressures on buildings from CFD simulations using ``OpenFOAM``
- User-defined buildings for wind loading input and structural response output
- Design structures including Multi-degree-of-freedom (``MDOF``) model, steel building model, ``OpenSees`` models, and ``OpenSeesPy`` models
- Output probabilistic building responses, velocities and pressure at any point in the fluid domain


Please visit the [WE-UQ Research Tool webpage](https://simcenter.designsafe-ci.org/research-tools/we-uq/)
for more resources related to this tool. Additionally, this page
provides more information on the NHERI SimCenter, including other SimCenter
applications, FAQ, and how to collaborate.



## Quick Links

- [Download Application](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/WE_UQ)
- [Step-by-Step Examples](https://nheri-simcenter.github.io/WE-UQ-Documentation/common/user_manual/examples/desktop/examples)
- [Documentation & Guides](https://nheri-simcenter.github.io/WE-UQ-Documentation)
- [Overview Web-Page](https://simcenter.designsafe-ci.org/research-tools/we-uq)
- [Forum & Feature Requests](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=5.0)


## Citing this Work

If you use ``WE-UQ`` [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.3274227.svg)](https://doi.org/10.5281/zenodo.3274227) in your research, please cite our software as:

```bibtex
@software{McKennaMelakuDingWanMackenzie-HelnweinYiGardnerElhaddad2024,
  author       = {Frank McKenna and
                  Abiy Melaku and
                  Fei Ding and
                  Jiawei Wan and
                  Peter Mackenzie-Helnwein and
                  Sang-ri Yi and
                  Michael Gardner and
                  Wael Elhaddad},
  title        = {NHERI-SimCenter/WE-UQ: Version 3.3.0},
  month        = april,
  year         = 2024,
  publisher    = {Zenodo},
  version      = {v3.3.0},
  doi          = {10.5281/zenodo.11087165},
  url          = {https://doi.org/10.5281/zenodo.11087165}
}
```

and include the NHERI SimCenter's workflow architecture [![DOI](https://img.shields.io/badge/10.3389--fbuil.2020.558706-blue?label=DOI)](https://www.frontiersin.org/articles/10.3389/fbuil.2020.558706) using:

```bibtex
@Article{Deierlein2020,
  author={Deierlein, Gregory G. and McKenna, Frank and Zsarnóczay, Adam and Kijewski-Correa, Tracy and Kareem, Ahsan and Elhaddad, Wael and Lowes, Laura and Schoettler, Matthew J. and Govindjee, Sanjay},   
  title={A Cloud-Enabled Application Framework for Simulating Regional-Scale Impacts of Natural Hazards on the Built Environment},      
  journal={Frontiers in Built Environment},      
  volume={6},           
  year={2020},      
  url={https://www.frontiersin.org/articles/10.3389/fbuil.2020.558706},       
  doi={10.3389/fbuil.2020.558706},      
  issn={2297-3362},   
}
```

---

## SimCenter Eco-System

The challenges of natural hazards engineering are addressed by the NHERI SimCenter through a suite of applications that provide cutting-edge tools for researchers, practitioners, and stakeholders. The applications are designed to work together to provide a comprehensive solution for natural hazards engineering. A puzzle-piece diagram of the SimCenter ecosystem is shown below:



<a href="https://github.com/NHERI-SimCenter/"><img width="75%" src="./icons/SimCenter_PuzzlePieces_Horizontal.png" align="center" /></a>



In reality, this is a software workflow representation of the PEER Performance-Based Earthquake Engineering (PBEE) framework that has been extended to include other natural hazards:



<a href="https://github.com/NHERI-SimCenter/"><img width="85%" src="./icons/SimCenter_PEER_PBE.png" align="center" /></a>



``WE-UQ`` is just one part of the [NHERI SimCenter](https://simcenter.designsafe-ci.org) ecosystem that provides cutting-edge open-source tools for natural hazards engineering. Tools like ``quoFEM``, ``EE-UQ``, ``WE-UQ``, ``HydroUQ``, ``PBE``, and ``R2D`` work together to provide a comprehensive solution for natural hazards engineering. The SimCenter ecosytem forms a modular hierarchy that allows users to pick and choose the tools they need for their specific research or engineering problem.



<img width=60% align="left" src="https://raw.githubusercontent.com/NHERI-SimCenter/WE-UQ/master/icons/SimCenter_Hierarchy.png" />

While ``R2D`` is the top-level application that provides a regional resilience assessment, ``EE-UQ``, ``WE-UQ``, and ``HydroUQ`` provide uncertainty quantified simulations for earthquake, wind, and water-borne natural hazards, respectively. ``quoFEM`` is the backend UQ functionality they use.

Additional tools, such as ``BRAILS`` and ``TInF``, have special use-cases including AI-augmentation of building stock and creation of turbulent wind inflow for OpenFOAM CFD simulations.


All applications are free, open-source, and available for download on the [DesignSafe-CI](https://www.designsafe-ci.org) website. See the table below for more information on each application:



| Application | Full Title | Download | GitHub | Version |
|:-----------:|:-----------|:--------:|:------:|:-------:|
| ``R2D`` | Regional Resilience Determination Application | [![Download R2D](https://img.shields.io/badge/Download-R2D-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/R2Dt) | [![GitHub R2D](https://img.shields.io/badge/git%20R2D-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/R2DTool) | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/R2DTool)](https://github.com/NHERI-SimCenter/R2DTool/releases/latest) |
| ``PBE`` | Performance-Based Engineering Application | [![Download PBE](https://img.shields.io/badge/Download-PBE-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/PBE) | [![GitHub PBE](https://img.shields.io/badge/git%20PBE-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/PBE) | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/PBE)](https://github.com/NHERI-SimCenter/PBE/releases/latest) |
| ``EE-UQ`` | Earthquake Engineering with Uncertainty Quantification Application | [![Download EE-UQ](https://img.shields.io/badge/Download-EE--UQ-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/EE_UQ) | [![GitHub EE-UQ](https://img.shields.io/badge/git%20EE--UQ-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/EE-UQ) | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/EE-UQ)](https://github.com/NHERI-SimCenter/EE-UQ/releases/latest) |
| ``WE-UQ`` | Wind Engineering with Uncertainty Quantification Application | [![Download WE-UQ](https://img.shields.io/badge/Download-WE--UQ-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/WE_UQ) | [![GitHub WE-UQ](https://img.shields.io/badge/git%20WE--UQ-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/WE-UQ)  | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/WE-UQ)](https://github.com/NHERI-SimCenter/WE-UQ/releases/latest) |
| ``HydroUQ`` | Water-Borne Hazards Engineering with Uncertainty Quantification Application | [![Download HydroUQ](https://img.shields.io/badge/Download-HydroUQ-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ) | [![GitHub HydroUQ](https://img.shields.io/badge/git%20HydroUQ-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/HydroUQ)  | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/HydroUQ)](https://github.com/NHERI-SimCenter/HydroUQ/releases/latest) |
| ``quoFEM`` | Quantified Uncertainty with Optimization for the Finite Element Method Application | [![Download quoFEM](https://img.shields.io/badge/Download-quoFEM-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/quoFEM) | [![GitHub quoFEM](https://img.shields.io/badge/git%20quoFEM-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/quoFEM) |  [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/quoFEM)](https://github.com/NHERI-SimCenter/quoFEM/releases/latest) |
| ``TInF`` | Turbulence Inflow Generation for CFD Application | [![Download TInF](https://img.shields.io/badge/Download-TInF-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community//SimCenter/Software/TurbulenceInflowTool) | [![GitHub TInF](https://img.shields.io/badge/git%20TInF-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/TurbulenceInflowTool) | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/TurbulenceInflowTool)](https://github.com/NHERI-SimCenter/TurbulenceInflowTool/releases/latest) | 
| ``BRAILS`` | Building Recognition with AI at Large-Scale Application | ``pip install BRAILS`` | [![GitHub BRAILS](https://img.shields.io/badge/git%20BRAILS-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/BRAILS) | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/BRAILS)](https://github.com/NHERI-SimCenter/BRAILS/releases/latest) |

---

## Getting Started

The ``WE-UQ`` application can be [downloaded](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/WE-UQ), [installed](https://nheri-simcenter.github.io/WE-UQ-Documentation/common/user_manual/installation/desktop/installation.html), [built](https://nheri-simcenter.github.io/WE-UQ-Documentation/common/developer_manual/how_to_build/desktop/how_to_build.html), and [launched](https://nheri-simcenter.github.io/WE-UQ-Documentation/common/user_manual/running/desktop/running.html) on Windows, Mac, and Linux operating systems. With a [free DesignSafe account](https://www.designsafe-ci.org/account/register/), you can run WE-UQ simulations remotely on powerful supercomputers including the ``Frontera``, and ``Stampede3`` systems.



### Download WE-UQ

The ``WE-UQ`` desktop application is available for download on Windows and Mac operating systems from the DesignSafe-CI website at the [WE-UQ Download Link](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/WE-UQ).


### Install WE-UQ

The ``WE-UQ`` installation instructions are available in the [WE-UQ Installation Guide](https://nheri-simcenter.github.io/WE-UQ-Documentation/common/user_manual/installation/desktop/installation.html)



### Build WE-UQ

The ``WE-UQ`` application can be built from source code on Linux, Windows, and Mac operating systems. The source code is available in this repository. 

If the Github CLI is installed on your system, Clone the repository using the following command:
```
git clone https://github.com/NHERI-SimCenter/WE-UQ.git
```

Otherwise, you can clone the repository on this page by clicking on the green "Code" button and then clicking on "Download ZIP". Extract the downloaded ZIP file to a location on your system.

Instructions on building the WE-UQ application from downloaded source code are available in the [WE-UQ How-To-Build Guide](https://nheri-simcenter.github.io/WE-UQ-Documentation/common/developer_manual/how_to_build/desktop/how_to_build.html)


### Launch WE-UQ

The ``WE-UQ`` application can be run by executing the ``WE_UQ`` executable file. The instructions to run the WE-UQ application are available in the [WE-UQ Documentation](https://nheri-simcenter.github.io/WE-UQ-Documentation/common/user_manual/running/desktop/running.html)



### Run WE-UQ Remotely

Users with a free DesignSafe account can use the ``WE-UQ`` desktop app to launch a remote job to run simulations on powerful supercomputers with ease.

[Sign-up for DesignSafe](https://www.designsafe-ci.org/account/register/)

Available systems are the ``Frontera``, ``Lonestar6``, and ``Stampede3`` supercomputers. Systems are located at the Texas Advanced Computing Center (TACC) and made available to the user through NSF's NHERI DesignSafe-CI, the cyberinfrastructure provider for NHERI. 


---

## Get Involved

``WE-UQ`` is an open-source project developed for practitioners, researchers, students, and stakeholders by our team of experts at the NHERI SimCenter. We welcome contributions from the community to help improve the application and add new features.


### Contributing to WE-UQ

Interested in contributing to the open-source ``WE-UQ`` project? Find out how in the [WE-UQ Documentation](https://nheri-simcenter.github.io/WE-UQ-Documentation/).

We encourage practitioners, researchers, and students to comment on what additional features or step-by-step examples they would like to see in ``WE-UQ``. If you want it, chances are many of your colleagues will also benefit from it. We appreciate all input from the wind engineering community during the active development of ``WE-UQ``.

Submit your requests on the [SimCenter forum](https://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=5.0).

### Contact Us

Message us on the [SimCenter Message Board](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=5.0) for any questions, feature requests, or issues.

| Developer | Email | Role |
|:----|:-----|:----|
| Abiy Melaku | afmelaku@berkeley.edu | [![Email](https://img.shields.io/badge/Main%20Dev-blue)](mailto:afmelaku@berkeley.edu) | 
| Fei Dinkg | fding@nd.edu | [![Email](https://img.shields.io/badge/Former%20Dev-blue)](mailto:fding@nd.edu) | 
| Frank McKenna | fmckenna@berkeley.edu | [![Email](https://img.shields.io/badge/Senior%20Dev-blue)](mailto:fmckenna@berkeley.edu) |
| NHERI SimCenter | nheri-simcenter@berkeley.edu | [![Email](https://img.shields.io/badge/SimCenter-blue)](mailto:nheri-simcenter@berkeley.edu) |



### Sign-up for Updates

Stay up-to-date with the latest news, updates, and releases with the [NHERI Newsletter](https://4407eb04.sibforms.com/serve/MUIEAIae4IGtEQHh04xSx9x2pNIIb4m-IjUaN83IpiIrwDW4CtpySmL9ec5ASFjgZSBYRNfgSLwXl1B8sLFSgVYB3Hc2JJP6ORmrNoj9ouHNiX8zAZVmsM1_A18STCEKs3cRP6OXJZGdvUfR7PZd5G0VN_DKVhibD3g9aRAWY7wkEfrCVeJnclbaTXMV8YuGf0KFMZQxOntb5M7Z) and the [SimCenter Newsletter](https://simcenter.designsafe-ci.org/survey/?_gl=1*1mn7c1n*_ga*MTMxNzc2NjI2MC4xNzA5MDIyOTAx*_ga_D96RT1T24K*MTcxNDQ0NDAwOS4xNC4xLjE3MTQ0NDU4NzAuMC4wLjA) newsletters.



---

## Release License
[![License](https://img.shields.io/badge/License-BSD%202--Clause-blue)](https://raw.githubusercontent.com/NHERI-SimCenter/WE-UQ/master/LICENSE)

``WE-UQ`` is released as an open-source research application under a [BSD 2-Clause License](https://nheri-simcenter.github.io/WE-UQ-Documentation/common/front-matter/license.html)



## Acknowledgement


This material is based upon work supported by the National Science Foundation under Grant [No. 1612843](https://www.nsf.gov/awardsearch/showAward?AWD_ID=1612843) and [No. 2131111](https://www.nsf.gov/awardsearch/showAward?AWD_ID=2131111). Any opinions, findings, conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the U.S. National Science Foundation.
