<?php

namespace app\api\model;

use think\Model;

class Contest extends Model
{
    //
    protected $autoWriteTimestamp = true;
    protected $pk = 'cid';

    public function getPrivateAttr($val) {
        $map = [
            1 => '私有',
            0 => '公开'
        ];
        return $map[$val];
    }

    public function getUidAttr($val) {
        $user = new User();
        return $user->get($val)->username;
    }

}
