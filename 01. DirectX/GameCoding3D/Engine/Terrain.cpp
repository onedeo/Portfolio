#include "pch.h"
#include "Terrain.h"
#include "MeshRenderer.h"
#include "Camera.h"

Terrain::Terrain() : Super(ComponentType::Terrain)
{
}

Terrain::~Terrain()
{
}

void Terrain::Create(int32 sizeX, int32 sizeZ, shared_ptr<Material> material)
{
    _sizeX = sizeX;
    _sizeZ = sizeZ;

    auto go = _gameObject.lock();
    if (go == nullptr) return;

    go->GetOrAddTransform();

    if (go->GetMeshRenderer() == nullptr)
        go->AddComponent(make_shared<MeshRenderer>());

    _mesh = make_shared<Mesh>();
    _mesh->CreateGrid(_sizeX, _sizeZ);

    go->GetMeshRenderer()->SetMesh(_mesh);
    go->GetMeshRenderer()->SetPass(0);
    go->GetMeshRenderer()->SetMaterial(material);

}

bool Terrain::Pick(int32 screenX, int32 screenY, Vec3& pickPos, float& distance)
{
    Matrix W = GetTransform()->GetWorldMatrix();
    Matrix V = Camera::S_MatView;
    Matrix P = Camera::S_MatProjection;

    Viewport& vp = GRAPHICS->GetViewport();

    Vec3 _near = vp.Unproject(Vec3(screenX, screenY, 0), W, V, P);
    Vec3 _far = vp.Unproject(Vec3(screenX, screenY, 1), W, V, P);

    Vec3 start = _near;
    Vec3 direction = _far - _near;
    direction.Normalize();

    Ray ray = Ray(start, direction);

    const auto& vertices = _mesh->GetGeometry()->GetVertices();

    for (int32 z = 0; z < _sizeZ; z++)
    {
        for (int32 x = 0; x < _sizeX; x++)
        {
            uint32 index[4];
            index[0] = (_sizeX + 1) * z + x;
            index[1] = (_sizeX + 1) * z + (x + 1);
            index[2] = (_sizeX + 1) * (z + 1) + x;
            index[3] = (_sizeX + 1) * (z + 1) + (x + 1);

            Vec3 p[4];
            for (int32 i = 0; i < 4; i++)
                p[i] = vertices[index[i]].position;

            //  [2]
            //   |	    \
			//  [0] - [1]
            if (ray.Intersects(p[0], p[1], p[2], OUT distance))
            {
                pickPos = ray.position + ray.direction * distance;
                return true;
            }

            //  [2] - [3]
            //   	\  |
            //		  [1]
            if (ray.Intersects(p[3], p[1], p[2], OUT distance))
            {
                pickPos = ray.position + ray.direction * distance;
                return true;
            }

        }
    }

    return false;
}
